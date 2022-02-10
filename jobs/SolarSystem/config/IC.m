% Number of bodies in the simulation
Npart = 9;
% Sun, Mercury, Venus, Earth, Mars, Jupiter, Saturn, Uranus, Neptune

% Masses of the bodies in kg
% m = [1.9885e30, 3.302e23, 4.8685e24, 5.97219e24, 6.4171e23, 1.89818722e27, 5.6834e26, 8.6813e25, 1.02409e26];
m = [1.9885e30, 0, 0, 0, 0,0, 0, 0, 0];


% Initial position of the bodies in meters
r0 = [
    -1.068108951496322E+09,  -2.212073002393702E+10, -1.085736592234813E+11, -2.627903751048988E+10, 2.069270543147017E+11 , 5.978410555886381E+11 , 9.576382282218235E+11 , 2.157706590772856E+12 , 2.513785451779509E+12
    -4.177210908491462E+08,  -6.682435921338345E+10, -3.784241757371509E+09, 1.445101984929515E+11 , -3.560689745239088E+09, 4.387048655696349E+11 , 9.821474893679625E+11 , -2.055242872276594E+12, -3.739265135509532E+12
    3.086887010002915E+07 ,  -3.461577076477692E+09, 6.190088659339075E+09 , 3.025245352813601E+07 , -5.147936537447235E+09, -1.520164176015472E+10, -5.518978744215649E+10, -3.559274281055415E+10, 1.907027540535474E+10
];

% Initial velocity of the bodies in meters/second
v0 = [
    9.305302656256911E+00 , 3.666229234452722E+04 , 8.984650886248794E+02 , -2.983052803412253E+04, 1.304308833322233E+03, -7.892632213479861E+03, -7.419580377753652E+03, 4.646953836957586E+03 , 4.475107938022004E+03
    -1.283177282717393E+01, -1.230266984222893E+04, -3.517203951420625E+04, -5.220465675237847E+03, 2.628158890420931E+04, 1.115034525890079E+04 , 6.725982467906618E+03 , 4.614361336283628E+03 , 3.062850546988970E+03
    -1.631700118015769E-01, -4.368336206255391E+03, -5.320225928762774E+02, -1.014855999592612E-01, 5.188465740839767E+02, 1.305100448596264E+02 , 1.775011906748625E+02 , -4.301369613442230E+01, -1.667293921151841E+01
];