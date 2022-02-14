addpath('../output/');
Schw;
plot( U(:, 3).*cos(U(:, 1)), U(:, 3).*sin(U(:, 1)));

saveas(gcf,"../output/orbita.png");
exit;