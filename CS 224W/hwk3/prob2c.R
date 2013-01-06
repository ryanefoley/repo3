#Problem 2c

fit = lm(log(log_h$count) ~ log_h$mid)
jpeg('rplot1.jpg')
plot(log_h$mids,log(log_h$counts), type='h', lwd=10, lend=2, ylab = 'Log Frequency', xlab = 'Log(x)', main = 'Log-Log Histogram of Generated Data')
abline(fit, lwd=3, col='yellow')
dev.off()

#Problem 2d
ccdf_hist = hist(log(1-power_cdf(rep(1:100000), x_min, alpha)), plot = FALSE)

jpeg('rplot2.jpg')

plot(ccdf_hist$mids, log(ccdf_hist$counts), type='h', lwd=10, lend=2, ylab = 'Log Frequency', xlab = 'Log(x)', main = 'Log-Log Histogram of Generated Data')
fit = lm(log(ccdf_hist$count) ~ ccdf_hist$mid)
abline(fit, lwd=3, col='yellow')

dev.off()