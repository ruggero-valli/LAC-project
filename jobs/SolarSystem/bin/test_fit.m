x0 = [-1,0.9,2.1]';
figure(1);
k = 1e-3;
plot(x0*k+13.413, x0.^2/1000+0.9732, '*', 'color', 'green');
hold on
xx = linspace(x0(1), x0(3));
plot(xx*k+13.413, xx.^2/1000+0.9732, '--', 'color', 'red');
plot(13.413, 0.9732, 'o', 'MarkerFaceColor','blue');
grid on
xlabel("t");
ylabel("r");

%%

figure(2);
for k = logspace(-10,0)
    x = x0*k+100;
    y = (x-100).^2;
    [xv,yv] = findmin1(x,y);
    scatter(k,abs(xv-100), 'black');
    hold on;
    [xv,yv] = findmin2(x,y);
    scatter(k,abs(xv-100), 'red');
    hold on;
end
grid on
set(gca, 'XScale', 'log')
set(gca, 'YScale', 'log')
legend(["fit", "analytical"])
xlabel("dt")
ylabel("estimated t_{peri}")





function [xv,yv] = findmin1(x,y)
    f=fit(x,y,'poly2');
    coef = coeffvalues(f);
    a = coef(1);
    b = coef(2);
    c = coef(3);
    xv = -b/(2*a);
    yv = c-b^2/(4*a);
end

function [xv,yv] = findmin2(x,y)
    k1 = (x(1)-x(2))*(x(1)-x(3));
    k2 = (x(2)-x(1))*(x(2)-x(3));
    k3 = (x(3)-x(1))*(x(3)-x(2));
    a = y(1)/k1 + y(2)/k2 + y(3)/k3;
    b = -y(1)*(x(2)+x(3))/k1 - y(2)*(x(1)+x(3))/k2 - y(3)*(x(1)+x(2))/k3;
    c = y(1)*x(2)*x(3)/k1 + y(2)*x(1)*x(3)/k2 + y(3)*x(1)*x(2)/k3;
    xv = -b/(2*a);
    yv = c-b^2/(4*a);
end
