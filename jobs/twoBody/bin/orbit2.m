prova;
units;
IC;

U_r = reshape(U(:, 1:6 ), [], 3, 2);
U_v = reshape(U(:, 7:12), [], 3, 2);

T = sqrt(L.*L.*L./M./G);

r0_norm = r0./L;
v0_norm = v0.*T./L;
m_norm = m./M;

R = orbit(U_r, U_v, v0_norm, r0_norm, m_norm);
theta = angolo(U_r, U_v, m_norm);
plot(R.*cos(theta), R.*sin(theta));
xlabel('R*cos(theta)');
ylabel('R*sin(theta)');
title('2 bodies orbit');

function F = orbit(U_r, U_v, v0_norm, r0_norm, m_norm)
mu = (m_norm(1)+m_norm(2));
[r, v, ~, ~] = coord_change(r0_norm(:,1), r0_norm(:,2), v0_norm(:,1), v0_norm(:, 2), m_norm);
mod = norm(r, 2);  
mod_v = norm(v, 2);
v_theta = (r(1).*v(2) - r(2).*v(1))./mod;       
e = sqrt(1+(mod.*v_theta.^2./mu).*((mod.*mod_v.^2/mu)-2));  
theta = angolo(U_r, U_v,m_norm);
a = (mu.*mod)./(2.*mu - mod.*mod_v.^2);

F = a.*(1-e.^2)./(1+e.*cos(theta)); 
end

function [r, v, r_g, v_g] = coord_change(r10, r20, v10, v20, m)
v_g = (m(1).*r10 + m(2).*r20)./(m(1)+m(2));
r_g = (m(1).*r10 + m(2).*r20)/(m(1)+m(2));
r = (m(1)+m(2)).*(r_g-r10)/m(2);
v = v20 - v10;
end

function theta = angolo(U_r, U_v, m_norm)
[r,~,~,~] = coord_change(U_r(:, :, 1), U_r(:,:,2), U_v(:,:,1), U_v(:,:,2), m_norm);
theta = atan2(r(:, 2),r(:,1));
end

