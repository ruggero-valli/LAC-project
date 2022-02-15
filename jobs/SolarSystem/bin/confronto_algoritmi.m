RK4 = [13554,579.2373,530.3858, 527.3288];
RK5 = [526.5903, 527.0196, 527.1196, 527.1214];
Yo = [1.0927e+04, 579.2373, 481.7079,524.2816];
steps = [20000, 40000, 80000,160000];
true = 532;

loglog(steps, abs(Yo-true)/true, '*-');
hold on
loglog(steps, abs(RK4-true)/true, '*-');
loglog(steps, abs(RK5-true)/true, '*-');
legend(["Yoshida", "RK4", "RK5"]);
grid on
xlabel("Number of integration steps")
yl = ylabel('relative error on precession rate');

