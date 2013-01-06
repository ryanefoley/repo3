x = [50, 100, 200, 400, 800, 1400]
y = [0.0525, 0.0312, 0.0125, 0.0150, 0.0125, 0.0100]

f = figure;
plot(x, y, 'o--')
ylabel('Misclassification Rate')
xlabel('Number of Emails Used in Training')
print(f, '-dpng', 'plot.png')
