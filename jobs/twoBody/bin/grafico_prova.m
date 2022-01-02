addpath('../output/');
prova;
plot3(U(:, 1), U(:, 2), U(:,3));
saveas(gcf,"../output/grafico_prova.png");
exit;