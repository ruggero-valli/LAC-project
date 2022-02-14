IC;
units;
T = sqrt(L*L*L/M/G);
% Import data - higher order
SS_RK5_80k;

U_r = reshape(U(:, 1:end/2 ), [], 3, Npart);
U_v = reshape(U(:, end/2+1:end), [], 3, Npart);
tH = t;
[r_vecH,~,~,~] = coord_change(U_r(:, :, 1), U_r(:,:,2), U_v(:,:,1), U_v(:,:,2), m(1), m(2));


% Import data - lower order

SS_RK4_80k;

U_r = reshape(U(:, 1:end/2 ), [], 3, Npart);
U_v = reshape(U(:, end/2+1:end), [], 3, Npart);
tL = t;
[r_vecL,~,~,~] = coord_change(U_r(:, :, 1), U_r(:,:,2), U_v(:,:,1), U_v(:,:,2), m(1), m(2));

err = sqrt(sum((r_vecH-r_vecL).^2,2))./sqrt(sum(r_vecH.^2,2));
%%
[tpH,rp_vecH, thetapH] = periastron(tH,r_vecH);
[tpL,rp_vecL, thetapL] = periastron(tL,r_vecL);

errrp = sqrt(sum((rp_vecH-rp_vecL).^2,2))./sqrt(sum(rp_vecH.^2,2));
errtp = abs(tpL-tpH)./abs(tpH);
errthetap = abs(thetapL-thetapH);


%%
figure();
loglog(tH,err,'.', Color="r");
hold on
loglog(tpH, errrp./i','.');
loglog(tpH, errtp./i','.');
loglog(tpH, errthetap./i','.');
legend(["rp", "tp", "thetap"]);

%%
figure()
plot(tpH*T/pi/1e7, thetapH*360*3600/2/pi)
hold on
plot(tpL*T/pi/1e7, thetapL*360*3600/2/pi)

%%
figure()
i = 1:length(errthetap);
plot(tpH, errthetap./i','.');
hold on
%plot(tpH, 2.7e-9*tpH/i');
%yline(2/360/3600*2*pi);


%%
plot(abs(thetapH-thetapL))
hold on
plot(thetapH)
plot(thetapL)
%%
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
        if ((idx <= delta) || (idx >= length(t)-delta))
            continue
        end
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

function f2 = toNyquist(f1, fny)
    f2 = mod(f1,2*fny);
    if f2 > fny
        f2 = 2*fny-f2;
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