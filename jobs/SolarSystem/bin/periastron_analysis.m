% Import data
SS_RK5_40k;
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

%%
% find the periastron of each orbit
[tp,rp_vec, thetap] = periastron(t,r_vec);

%%
% plot the periastron precession in time
figure()
tp_years = tp*T/(pi*1e7);
t_years = t*T/(pi*1e7);
thetap_arcsec = thetap*360*3600/(2*pi);
plot(tp_years, thetap_arcsec,'o-', MarkerSize=3, MarkerFaceColor="b");
grid on
hold on
p = polyfit(tp_years,thetap_arcsec,1);
plot(t_years, p(1)*t_years+p(2));
precession3 = p(1)*100; % arcsec per century
xlabel("time (year)")
ylabel("precession angle ('')")

%%
figure()
plot(diff(tp)-mean(diff(tp)));
%%
figure()
% subtract the slope
osc = thetap-p(1)*tp-p(2);
plot(tp, osc,'o-',MarkerSize=3, MarkerFaceColor="b");

%periods of the planets
pm = 87.97;
pv = 224.70;
pe = 365.26;
pM = 686.98;
pj = 4332.82;
pS = 10755.70;

figure();
hold on
% plot some vertical lines at the frequency of the planets and their
% harmonics
xline(1/pv*pe, Color="r", LineWidth=2)
xline(1/pe*pe, Color="b", LineWidth=2)
xline(1/pj*pe, Color="g", LineWidth=2)
xline(1/pM*pe)
xline(1/pS*pe)
xline(2/pv*pe, Color="r")
xline((-1/pm+3/pv)*pe, Color="r")
xline((-1/pm+4/pv)*pe, Color="r")
xline(2/pe*pe, Color="b")
xline(3/pe*pe, Color="b")
xline(4/pe*pe, Color="b")
xline(2/pj*pe, Color="g")
xline(3/pj*pe, Color="g")
xline(4/pj*pe, Color="g")
grid on

% calculate the power spectrum
ps = abs(fft(osc));
f = linspace(0,1/pm*pe, length(tp));
plot(f, ps)

legend("Venus", "Earth", "Jupiter")
grid on
xlabel("frequency (year^{-1})")
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
    
    delta = 3;
    i = 0;
    % for every local minima, find the exact point
    for idx = transpose(min_idx)
        i = i+1;
        i_span = (-delta:delta) + idx;
        t_span = t(i_span);
        r_span = r(i_span);
        r_vec_span = r_vec(i_span,:);

        [tp(i), rp(i)] = findMin(t_span, r_span);
        
        %plot(t_span, r_span, '*');
        %hold on
        %plot(tp(i), rp(i), 'o', "MarkerFaceColor","blue");
        %tt = linspace(t_span(1), t_span(3));
        %plot(tt, a*tt.^2+b*tt+c);
        
        for j = 1:3
            rp_vec(i,j) = interp1(t_span, r_vec_span(:,j), tp(i), 'spline');
            %plot(t_span, r_vec_span(:,1), '*');
            %hold on
            %plot(tp(i), rp_vec(i, 1), 'o', "MarkerFaceColor","blue");
            %tt = linspace(t_span(1), t_span(3));
            %plot(tt, a*tt.^2+b*tt+c);
        end
        thetap(i) = angolo(rp_vec(i,:), rp_vec(1,:));
    end
end

function [xm, ym] = findMin(x,y)
    f = griddedInterpolant(x,y,'spline'); % spline seems to be the best
    [xm, ym] = fminbnd(@(x) f(x), x(1), x(end));
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

% function [a,b,c] = parabola(x,y)
%     % find the coefficients a,b and c of the parabola y = a*x.^2+b*x+c
%     % given the value in three points
%     k1 = (x(1)-x(2))*(x(1)-x(3));
%     k2 = (x(2)-x(1))*(x(2)-x(3));
%     k3 = (x(3)-x(1))*(x(3)-x(2));
%     a = y(1)/k1 + y(2)/k2 + y(3)/k3;
%     b = -y(1)*(x(2)+x(3))/k1 - y(2)*(x(1)+x(3))/k2 - y(3)*(x(1)+x(2))/k3;
%     c = y(1)*x(2)*x(3)/k1 + y(2)*x(1)*x(3)/k2 + y(3)*x(1)*x(2)/k3;
% end

% function [a,b,c] = parabola(x,y)
%     % parabolic fit of the points around the minimum
%     f=fit(x,y,'poly4');
%     coef = coeffvalues(f);
%     a = coef(1);
%     b = coef(2);
%     c = coef(3);
% end
