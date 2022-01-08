prova;
units;
IC;

U_r = reshape(U(:, 1:6 ), [], 3, 2);
U_v = reshape(U(:, 7:12), [], 3, 2);

T = sqrt(L*L*L/M/G);
G = 1;

r0 = r0/L;
v0 = v0*T/L;
m = m/M;

[r,v,~,~] = coord_change(U_r(:, :, 1), U_r(:,:,2), U_v(:,:,1), U_v(:,:,2), m);
[r0, v0, ~, ~] = coord_change(r0(:,1), r0(:,2), v0(:,1), v0(:, 2), m);
theta = angolo(r);
R = orbit(theta, r0, v0, m(1)+m(2));

%%
figure();
plot(R.*cos(theta), R.*sin(theta), '.');
hold on
plot(r(:,1), r(:,2),'.');
xlabel('R*cos(theta)');
ylabel('R*sin(theta)');
title('2 bodies orbit');

figure();
mod = sqrt(sum(r.^2,2));
err = (R-mod)./R;
plot(err,'.');
max(abs(err))

%%
[tp, thetap, rp] = periastron(t,mod,theta);
%%
figure()
plot(rp.*cos(thetap),rp.*sin(thetap),'.');
hold on
plot(mod.*cos(theta),mod.*sin(theta),'.');

%%
figure()
plot(tp, thetap-pi,'.');

%%
figure();
plot(tp, rp,'.');
hold on
plot(t,mod,'.');

%%
function R = orbit(theta, r0, v0, mu)
    mod_r = norm(r0);  
    mod_v = norm(v0);
    v_theta = (r0(1).*v0(2) - r0(2).*v0(1))/mod_r;
    v_r = (r0(1)*v0(1)+r0(2)*v0(2))/mod_r;
    e = sqrt(1+(mod_r.*v_theta^2/mu)*((mod_r*mod_v^2/mu)-2));  
    a = (mu*mod_r)/(2*mu - mod_r*mod_v^2);
    
    arg = (a*(1-e^2)-mod_r)/(e*mod_r);
    s = sign(v_theta*v_r);
    if (s == 0)
        s=1;
    end
    if arg > 1
        arg = 1;
    end
    if arg < -1
        arg = -1;
    end
    Dtheta = s.*acos(arg) - atan2(r0(2), r0(1));
    R = a.*(1-e.^2)./(1+e.*cos(theta+Dtheta));
end

function [r, v, r_g, v_g] = coord_change(r10, r20, v10, v20, m)
    v_g = (m(1)*v10 + m(2)*v20)/(m(1)+m(2));
    r_g = (m(1)*r10 + m(2)*r20)/(m(1)+m(2));
    r = r20 - r10;
    v = v20 - v10;
end

function theta = angolo(r)
    theta = atan2(r(:, 2),r(:,1));
end

function [tp, thetap, rp] = periastron(t,r,theta)
    % look for local minima
    [~,min_idx] = findpeaks(-r(:,1));

    tp = zeros(length(min_idx));
    thetap = zeros(length(min_idx));
    rp = zeros(length(min_idx));
    
    delta = 1;
    i = 0;
    % for every local minima, find the exact point
    for idx = transpose(min_idx)
        i = i+1;
        if ((idx<delta) || (idx > length(t)-delta))
            continue
        end
        i_span = (-delta:delta) + idx;
        t_span = t(i_span);
        r_span = r(i_span);
        theta_span = theta(i_span);
        % parabolic fit of the points around the minimum
        f=fit(t_span,r_span,'poly2');
        coef = coeffvalues(f);
        a = coef(1);
        b = coef(2);
        c = coef(3);
        % a,b,c are the three coefficients of a parabola
        tp(i) = -b/(2*a);
        rp(i) = c-b^2/(4*a);
        
        % this line is a workaround for when the periastron is near
        % theta=pi. Need to find something better
        theta_span(theta_span < 0.1) = theta_span(theta_span < 0.1)+2*pi;
        % find the theta of periastron through a linear interpolation
        thetap(i) = interp1(t_span, theta_span, tp(i));
    end
end

