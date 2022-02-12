SS;
for i = 0:8
    %plot(U(:, i*3+1)-U(:, 1), U(:, i*3+2)-U(:, 2));
    plot(U(:, i*3+1), U(:, i*3+2));
    hold on
end
%exit;