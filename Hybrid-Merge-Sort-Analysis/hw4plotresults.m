% MATLAB script to read and plot sorting results

%loading data from files
best_case = load('bestcase.txt');
worst_case = load('worstcase.txt');
avg_case = load('averagecase.txt');

%extract kvalues and times
k_values = best_case(:,1); %first column contains kvalues
best_times = best_case(:,2); %second column contains times
worst_times = worst_case(:,2);
avg_times = avg_case(:,2);

%plot results
figure;
plot(k_values, best_times, '-o', 'LineWidth', 2, 'DisplayName', 'Best Case');
hold on;
plot(k_values, worst_times, '-s', 'LineWidth', 2, 'DisplayName', 'Worst Case');
plot(k_values, avg_times, '-^', 'LineWidth', 2, 'DisplayName', 'Average Case');

%customize plot
xlabel('k (Threshold for Insertion Sort)');
ylabel('Time (seconds)');
title('Hybrid Merge Sort Performance');
legend('Location', 'best');
grid on;

%using log scale if values span a large range
set(gca, 'XScale', 'log', 'YScale', 'log'); 
