prova;
units;
IC;

U_r = reshape(U(:, 1:6 ), [], 3, 2);
U_v = reshape(U(:, 7:12), [], 3, 2);

T = sqrt(L*L*L/M/G);
G = 1;

r0_vec = r0/L;
v0_vec = v0*T/L;
m = m/M;

[r_vec,v_vec,~,~] = coord_change(U_r(:, :, 1), U_r(:,:,2), U_v(:,:,1), U_v(:,:,2), m);
[r0_vec, v0_vec, ~, ~] = coord_change(r0_vec(:,1), r0_vec(:,2), v0_vec(:,1), v0_vec(:, 2), m);
theta = angolo(r_vec);
R = orbit(theta, r0_vec, v0_vec, m(1)+m(2));
r = sqrt(sum(r_vec.^2,2));

%%
figure();
plot(R.*cos(theta), R.*sin(theta), '.');
hold on
plot(r.*cos(theta), r.*sin(theta), '.');
xlabel('R*cos(theta)');
ylabel('R*sin(theta)');
title('2 bodies orbit');

figure();
err = (R-r)./R;
plot(err,'.');
max(abs(err))

%%
%t = transpose(linspace(0,400,1000));
%theta = mod(t+pi, 2*pi)-pi;
%R = orbit(theta, r0_vec, v0_vec, m(1)+m(2));
[tp,rp,thetap] = periastron(t,r,theta);
%%
figure()
plot(rp.*cos(thetap),rp.*sin(thetap),'.');
hold on
plot(r.*cos(theta),r.*sin(theta),'.');

%%
figure()
plot(tp, thetap-pi,'.');
hold on
plot(tp, thetap+pi, '.');

%%
figure()
plot(thetap, rp,'.');
hold on
plot(theta, r,'.');


%%
figure();
plot(tp, rp,'.');
%hold on
%plot(t,r,'.');

%%
figure();
plot(t,theta, '.')
hold on;
plot(tp, thetap, '.')

%%
function R = orbit(theta, r0_vec, v0_vec, mu)
    r = norm(r0_vec);  
    v = norm(v0_vec);
    v_theta = (r0_vec(1).*v0_vec(2) - r0_vec(2).*v0_vec(1))/r;
    v_r = (r0_vec(1)*v0_vec(1)+r0_vec(2)*v0_vec(2))/r;
    e = sqrt(1+(r.*v_theta^2/mu)*((r*v^2/mu)-2));  
    a = (mu*r)/(2*mu - r*v^2);
    
    arg = (a*(1-e^2)-r)/(e*r);
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
    Dtheta = s.*acos(arg) - atan2(r0_vec(2), r0_vec(1));
    R = a.*(1-e.^2)./(1+e.*cos(theta+Dtheta));
end

function [r_vec, v_vec, rg_vec, vg_vec] = coord_change(r10_vec, r20_vec, v10_vec, v20_vec, m)
    vg_vec = (m(1)*v10_vec + m(2)*v20_vec)/(m(1)+m(2));
    rg_vec = (m(1)*r10_vec + m(2)*r20_vec)/(m(1)+m(2));
    r_vec = r20_vec - r10_vec;
    v_vec = v20_vec - v10_vec;
end

function theta = angolo(r_vec)
    theta = atan2(r_vec(:, 2),r_vec(:,1));
end

function [tp, rp, thetap] = periastron(t,r,theta)
    % look for local minima
    [~,min_idx] = findpeaks(-r(:,1));
    tp = zeros(length(min_idx),1);
    thetap = zeros(length(min_idx),1);
    rp = zeros(length(min_idx),1);
    
    delta = 1;
    i = 0;
    %figure();
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

        % checking if the periastron is near 2pi and the theta_span
        % overlaps with the jump from 2pi to 0.
        if (max(theta_span) - min(theta_span) > pi)
            theta_span(theta_span < pi) = theta_span(theta_span < pi)+2*pi;
        end
        
        % parabolic fit of the points around the minimum
        f=fit(theta_span,r_span,'poly2');
        coef = coeffvalues(f);
        a = coef(1);
        b = coef(2);
        c = coef(3);
        % a,b,c are the three coefficients of a parabola

        % Calcolo analitico dei coefficienti. Non è preciso come il fit
        %k1 = (theta_span(1)-theta_span(2))*(theta_span(1)-theta_span(3));
        %k2 = (theta_span(2)-theta_span(1))*(theta_span(2)-theta_span(3));
        %k3 = (theta_span(3)-theta_span(1))*(theta_span(3)-theta_span(2));
        %a = r_span(1)/k1 + r_span(2)/k2 + r_span(3)/k3;
        %b = -r_span(1)*(theta_span(2)+theta_span(3))/k1 - r_span(2)*(theta_span(1)+theta_span(3))/k2 - r_span(3)*(theta_span(1)+theta_span(2))/k3;
        %c = r_span(1)*theta_span(2)*theta_span(3)/k1 + r_span(2)*theta_span(1)*theta_span(3)/k2 + r_span(3)*theta_span(1)*theta_span(2)/k3;

        thetap(i) = -b/(2*a);
        rp(i) = c-b^2/(4*a);
        
        % Plot showing the fitted curves
        %plot(theta_span+i,r_span,'b.');
        %hold on;
        %plot(thetap(i)+i, rp(i),'r.');
        %ttheta = linspace(theta_span(1), theta_span(3));
        %plot(ttheta+i, a.*ttheta.*ttheta+b.*ttheta+c,'g');
        
        % find the time of periastron through a linear interpolation
        tp(i) = interp1(theta_span, t_span, thetap(i));
        thetap = mod(thetap+pi, 2*pi)-pi;
    end
end
