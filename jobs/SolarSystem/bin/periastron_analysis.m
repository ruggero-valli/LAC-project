% Import data
SS;
units;
IC;

U_r = reshape(U(:, 1:end/2 ), [], 3, Npart);
U_v = reshape(U(:, end/2+1:end), [], 3, Npart);

% define units and initial conditions
T = sqrt(L*L*L/M/G);
G = 1;

r0_vec = r0/L;
v0_vec = v0*T/L;
m = m/M;

% move to the coordinate system centered on the sun
[r_vec,v_vec,~,~] = coord_change(U_r(:, :, 1), U_r(:,:,2), U_v(:,:,1), U_v(:,:,2), m(1), m(2));
[r0_vec, v0_vec, ~, ~] = coord_change(r0_vec(:,1), r0_vec(:,2), v0_vec(:,1), v0_vec(:, 2), m(1), m(2));
r = sqrt(sum(r_vec.^2,2));

%%
% find the periastron of each orbit
[tp,rp_vec, thetap] = periastron(t,r_vec);

%%
% plot the periastron precession in time
figure()
plot(tp, thetap,'o-');
grid on
hold on
p = polyfit(tp,thetap,1);
plot(t, p(1)*t+p(2))

%%
figure()
% subtract the slope
osc = thetap-p(1)*tp-p(2);
plot(tp, osc,'o-');

% calculate the power spectrum
ps = abs(fft(osc));
f = linspace(0,1/87, length(tp));
semilogx(1./f,ps)
grid on
xlabel("days")
ylabel("power spectrum")

%% Functions
function [r_vec, v_vec, rg_vec, vg_vec] = coord_change(r10_vec, r20_vec, v10_vec, v20_vec, m1, m2)
    vg_vec = (m1*v10_vec + m2*v20_vec)/(m1+m2);
    rg_vec = (m1*r10_vec + m2*r20_vec)/(m1+m2);
    r_vec = r20_vec - r10_vec;
    v_vec = v20_vec - v10_vec;
end

function [tp, rp_vec, thetap] = periastron(t,r_vec)
    % calculates the time of periastron tp, the vector of periastron
    % rp_vec and the angle of precession for each orbit

    r = sqrt(sum(r_vec.^2,2));

    % look for local minima
    [~,min_idx] = findpeaks(-r(:,1));
    tp = zeros(length(min_idx),1); % periastron time
    rp_vec = zeros(length(min_idx),3); % periastron vector
    thetap = zeros(length(min_idx),1); % periastron angle
    
    delta = 1;
    i = 0;
    % for every local minima, find the exact point
    for idx = transpose(min_idx)
        i = i+1;
        i_span = (-delta:delta) + idx;
        t_span = t(i_span);
        r_span = r(i_span);
        r_vec_span = r_vec(i_span,:);
        
        % parabolic fit of the points around the minimum
        %f=fit(t_span,r_span,'poly2');
        %coef = coeffvalues(f);
        %a = coef(1);
        %b = coef(2);
        %c = coef(3);

        % parabola passing for the three points near the periastron
        [a,b,c] = parabola(t_span, r_span);

        tp(i) = -b/(2*a);
        rp(i) = c-b^2/(4*a);
        
        %plot(t_span, r_span, '*');
        %hold on
        %plot(tp(i), rp(i), 'o', "MarkerFaceColor","blue");
        %tt = linspace(t_span(1), t_span(3));
        %plot(tt, a*tt.^2+b*tt+c);
        
        for j = 1:3
            [a,b,c] = parabola(t_span, r_vec_span(:,j));
            rp_vec(i,j) = a*tp(i).^2 + b*tp(i) + c;
            %plot(t_span, r_vec_span(:,1), '*');
            %hold on
            %plot(tp(i), rp_vec(i, 1), 'o', "MarkerFaceColor","blue");
            %tt = linspace(t_span(1), t_span(3));
            %plot(tt, a*tt.^2+b*tt+c);
        end
        thetap(i) = angolo(rp_vec(i,:), rp_vec(1,:));
    end
end

function [a,b,c] = parabola(x,y)
    % find the coefficients a,b and c of the parabola y = a*x.^2+b*x+c
    % given the value in three points
    k1 = (x(1)-x(2))*(x(1)-x(3));
    k2 = (x(2)-x(1))*(x(2)-x(3));
    k3 = (x(3)-x(1))*(x(3)-x(2));
    a = y(1)/k1 + y(2)/k2 + y(3)/k3;
    b = -y(1)*(x(2)+x(3))/k1 - y(2)*(x(1)+x(3))/k2 - y(3)*(x(1)+x(2))/k3;
    c = y(1)*x(2)*x(3)/k1 + y(2)*x(1)*x(3)/k2 + y(3)*x(1)*x(2)/k3;
end

function theta = angolo(vec1, vec2)
    % find the angle between two 3d vectors
    mod1 = sqrt(sum(vec1.^2));
    mod2 = sqrt(sum(vec2.^2));
    
    theta = acos(vec1*vec2'/mod1/mod2);
    if imag(theta) ~= 0
        theta = 0;
    end
end
