x = [50, 100, 200, 400, 800, 1400]
y = [0.4238, 0.3275, 0.1963, 0.0788, 0.0537, 0.0488]

f = figure;
plot(x, y, 'o--')
ylabel('Misclassification Rate')
xlabel('Number of Emails Used in Training')
print(f, '-dpng', 'plot.png')
