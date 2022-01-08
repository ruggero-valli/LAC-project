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
theta = angolo(r);
R = orbit(theta, v0, r0, m);
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


function R = orbit(theta, v0, r0, m)
mu = (m(1)+m(2));
[r, v, ~, ~] = coord_change(r0(:,1), r0(:,2), v0(:,1), v0(:, 2), m);
mod_r = norm(r);  
mod_v = norm(v);
v_theta = (r(1).*v(2) - r(2).*v(1))/mod_r;
v_r = (r(1)*v(1)+r(2)*v(2))/mod_r;
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
Dtheta = s.*acos(arg) - atan2(r(2), r(1));
R = a.*(1-e.^2)./(1+e.*cos(theta+Dtheta));
end

function [r, v, r_g, v_g] = coord_change(r10, r20, v10, v20, m)
v_g = (m(1).*r10 + m(2).*r20)./(m(1)+m(2));
r_g = (m(1).*r10 + m(2).*r20)/(m(1)+m(2));
r = (m(1)+m(2)).*(r_g-r10)/m(2);
v = v20 - v10;
end

function theta = angolo(r)
theta = atan2(r(:, 2),r(:,1));
end

