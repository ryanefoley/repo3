x = [50, 100, 200, 400, 800, 1400]
y = [.0387/0.0525, .0262/0.0312, .0262/0.0125, .0187/0.0150, .0175/0.0125, .0163/0.0100]

f = figure;
plot(x, y, 'o--')
ylabel('NB / SVM')
xlabel('Number of Emails Used in Training')
print(f, '-dpng', 'plot.png')
