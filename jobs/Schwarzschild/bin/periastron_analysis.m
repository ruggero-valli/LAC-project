%U vector contains four coloumns phi, tt, r, v, one for each time step
%La notazione U(:, 1) prende tutta la prima colonna, quindi tutti i phi
Schw;
units;
IC;

%Trajectory plot
plot(U(:, 3).*cos(U(:, 1)), U(:, 3).*sin(U(:, 1)), '.');
%%
%In questo caso r0 è un vettore 1x3 con le coordinate iniziali relative del
%sistema Sole-Mercurio e lo stesso vale per v0
T = sqrt(L*L*L/M/G);
G = 1;

%r0_vec = r0/L;
%v0_vec = v0*T/L;
m = m/M;

%I dati sono già in coordinate polari
r = U(:, 3)/L;
phi = mod(U(:, 1), 2*pi);
v = U(:, 4)*T/L;

[tp, phi_p] = periastron(t, r, phi);
plot(tp, phi_p, 'o');
%%
tp_years = tp*T/(pi*1e7);
t_years = t*T/(pi*1e7);
phip_arcsec = phi_p*360*3600/(2*pi);
plot(tp_years, phip_arcsec, 'o-', MarkerSize=3, MarkerFaceColor="b" )
grid on
hold on
p = polyfit(tp_years, phip_arcsec,1);
plot(t_years, p(1)*t_years+p(2));
precession = p(1)*100 % arcsec per century

function [tp, phi_p] = periastron(t, r, phi)

    % look for local minima
    [~,min_idx] = findpeaks(-r(:,1));
    %tp = zeros(length(min_idx),1); % periastron time
    phi_p = zeros(length(min_idx), 1);
    %rp = zeros(length(min_idx), 1);
    tp = zeros(length(min_idx), 1);
 
    delta = 3;
    i = 0;
    % for every local minima, find the exact point
    for idx = transpose(min_idx)
        i = i+1;
        i_span = (-delta:delta) + idx;
        %vettori contenenti i tempi e gli r nei 7 punti intorno ai minimi
        t_span = t(i_span);
        %r_span = r(i_span);
        phi_span = phi(i_span);

        %[phi_p(i), rp(i)] = findMin(phi_span, r_span);
        [tp(i), phi_p(i)] = findMin(t_span, phi_span);
    end
        
end

function [xm, ym] = findMin(x,y)
    f = griddedInterpolant(x,y,'spline'); % spline seems to be the best
    [xm, ym] = fminbnd(@(x) f(x), x(1), x(end));
end













