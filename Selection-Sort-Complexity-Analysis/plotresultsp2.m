% Data for selection sort execution times
n = [100, 500, 1000, 5000, 20000, 50000]; % Input sizes

worst_case = [3.7e-05, 0.00075, 0.002666, 0.033139, 0.104848, 2.63035];
best_case = [3.1e-05, 0.000729, 0.002559, 0.027037, 0.106247, 2.64274];
average_case = [3.59e-05, 0.0007689, 0.001977, 0.0265869, 0.106725, 2.65999];

% Plot the results
figure;
loglog(n, worst_case, '-o', 'LineWidth', 2, 'DisplayName', 'Worst Case');
hold on;
loglog(n, best_case, '-s', 'LineWidth', 2, 'DisplayName', 'Best Case');
loglog(n, average_case, '-^', 'LineWidth', 2, 'DisplayName', 'Average Case');

% Labels and title
xlabel('Input Size (n)');
ylabel('Execution Time (seconds)');
title('Selection Sort Time Complexity');
legend('Location', 'northwest');
grid on;
hold off;
