%% Units and initial conditions
units;
IC;

T = sqrt(L*L*L/M/G);
G = 1;

r0_vec = r0/L;
v0_vec = v0*T/L;
m = m/M;

[r0_vec, v0_vec, ~, ~] = coord_change(r0_vec(:,1), r0_vec(:,2), v0_vec(:,1), v0_vec(:, 2), m);

%% Import data
twoBody_RK5;

U_r = reshape(U(:, 1:6 ), [], 3, 2);
U_v = reshape(U(:, 7:12), [], 3, 2);
[r_vec,~,~,~] = coord_change(U_r(:, :, 1), U_r(:,:,2), U_v(:,:,1), U_v(:,:,2), m);
theta1 = angolo(r_vec);
r1 = sqrt(sum(r_vec.^2,2));

twoBody_RK4;

U_r = reshape(U(:, 1:6 ), [], 3, 2);
U_v = reshape(U(:, 7:12), [], 3, 2);
[r_vec,~,~,~] = coord_change(U_r(:, :, 1), U_r(:,:,2), U_v(:,:,1), U_v(:,:,2), m);
theta2 = angolo(r_vec);
r2 = sqrt(sum(r_vec.^2,2));

twoBody_Yo;

U_r = reshape(U(:, 1:6 ), [], 3, 2);
U_v = reshape(U(:, 7:12), [], 3, 2);
[r_vec,~,~,~] = coord_change(U_r(:, :, 1), U_r(:,:,2), U_v(:,:,1), U_v(:,:,2), m);
theta3 = angolo(r_vec);
r3 = sqrt(sum(r_vec.^2,2));

twoBody_Ve;

U_r = reshape(U(:, 1:6 ), [], 3, 2);
U_v = reshape(U(:, 7:12), [], 3, 2);
[r_vec,~,~,~] = coord_change(U_r(:, :, 1), U_r(:,:,2), U_v(:,:,1), U_v(:,:,2), m);
theta4 = angolo(r_vec);
r4 = sqrt(sum(r_vec.^2,2));

R = orbit(theta1, r0_vec, v0_vec, m(1)+m(2));

%%
figure();
semilogy(t*T/(pi*1e7), movmean(abs(r1-R)./R, 200));
hold on
semilogy(t*T/(pi*1e7), movmean(abs(r2-R)./R,200));
semilogy(t*T/(pi*1e7), movmean(abs(r3-R)./R,200));
semilogy(t*T/(pi*1e7), movmean(abs(r4-R)./R,200));
legend(["RK5", "RK4", "Yoshida", "Verlet"])
xlabel("time (years)")
ylabel("relative error on the solution")
grid on
%%
[tp1,rp1,thetap1] = periastron(t,r1,theta1);
[tp2,rp2,thetap2] = periastron(t,r2,theta2);
[tp3,rp3,thetap3] = periastron(t,r3,theta3);
[tp4,rp4,thetap4] = periastron(t,r4,theta4);
%%
figure();
semilogy(tp1*T/(pi*1e7), abs(thetap1)*360*3600/(2*pi));
hold on
semilogy(tp2*T/(pi*1e7), abs(thetap2)*360*3600/(2*pi));
semilogy(tp3*T/(pi*1e7), abs(thetap3)*360*3600/(2*pi));
semilogy(tp4*T/(pi*1e7), abs(thetap4)*360*3600/(2*pi));
legend(["RK5", "RK4", "Yoshida", "Verlet"])
xlabel("time (years)")
ylabel("error on the angle of periastron ('')")
grid on



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
    
    delta = 3;
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
            theta_span(theta_span < 0) = theta_span(theta_span < 0)+2*pi;
        end
           
        [thetap(i), rp(i)] = findMin(theta_span, r_span);
        
        % Plot showing the fitted curves
        %plot(theta_span+i,r_span,'b.');
        %hold on;
        %plot(thetap(i)+i, rp(i),'r.');
        %ttheta = linspace(theta_span(1), theta_span(3));
        %plot(ttheta+i, a.*ttheta.*ttheta+b.*ttheta+c,'g');
        
        % find the time of periastron through a linear interpolation
        tp(i) = interp1(theta_span, t_span, thetap(i), 'spline');
        thetap = mod(thetap+pi, 2*pi)-pi;
    end
end


function [xm, ym] = findMin(x,y)
    f = griddedInterpolant(x,y,'spline'); % spline seems to be the best
    [xm, ym] = fminbnd(@(x) f(x), x(1), x(end));
end