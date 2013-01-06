#Problem 2b - Generating Power Law Distn

alpha = 2
x_min = 1

power_cdf = function(x, x_min, alpha){
	result = 1-(x/x_min)^(-alpha + 1)
	return(result)
}	

power_pdf = function(x, x_min, alpha){
	result = ((alpha -1)/x_min)*(x/x_min)^-alpha
	return(result)
}	

inv_power_cdf = function(y, x_min, alpha){
	x = x_min*(1-y)^(1/(-alpha + 1))
	return(x)
}
#jpeg('rplot2.jpg')
sample = inv_power_cdf(runif(100000), x_min, alpha)

log_sample = log(sample)
log_h = hist(log_sample, plot = FALSE)
plot(log_h$count, log="y", type='h', lwd=10, lend=2, ylab = 'Log Frequency', xlab = 'Log(x)', main = 'Log-Log Histogram of Generated Data')

#dev.off()

#jpeg('rplot1.jpg')
#Log-Log with Probability in Y axis instead of counts
#plot(log_h$mids, log(log_h$count/sum(log_h$count)), type='h', lwd=10, lend=2, main = 'Log-Log Normalized Histogram of Generated Data', ylab = 'Log Probability', xlab = 'Log(x)' )

#dev.off()


