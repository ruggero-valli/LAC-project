SS;
col = ["yellow", "cyan", "magenta", "blue", "red", "black", "green"];
for i = 0:6
    plot(U(:, i*3+1)-U(:, 1), U(:, i*3+2)-U(:, 2), 'Color',col(i+1));
    plot(U(end, i*3+1)-U(end, 1), U(end, i*3+2)-U(end, 2), 'o', 'MarkerFaceColor',col(i+1));
    hold on
end
axis equal
%exit;