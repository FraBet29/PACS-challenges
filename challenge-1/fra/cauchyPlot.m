clear
close all
clc

data = readmatrix("output.csv");

tn = data(1, :);
un = data(2, :);

y = @(t) log(1 - t.^2/2); % exact solution

figure()
plot(tn, y(tn), '--k')
hold on
plot(tn, un, '*r')
legend('u', 'u_n')
xlabel('t [-]')
ylabel('y [-]')

conv_data = readmatrix("error.csv");
h = conv_data(1, :);
eh = conv_data(2, :);

figure()
loglog(h, eh, '--*')
hold on
loglog(h, h)
loglog(h, h.^2)
legend('e_h', 'h', 'h^2')
xlabel('h [-]')
ylabel('error [-]')
