#functions used later in algo
g = function(u) tanh(u)
gprime = function(u) 1-tanh(u)^2

#initialize data
source("http://www-stat.stanford.edu/~tibs/sta306b/ica-data.R")

#center data - here the data matrix x is pxn
x = t(scale(x, scale = FALSE))

#Whiten data
sigma = cov(t(x))
sigma.svd = svd(sigma)
xwig = sigma.svd$u%*%diag(sigma.svd$d^(-1/2))%*%t(sigma.svd$v)%*%x

#Initialize w, the weight matrix, as pxp matrix with all random N(0,1) elements 
w = matrix(rnorm(nrow(x)^2), nrow = nrow(x), ncol = nrow(x) )

#Subtract out other components and renormalize w
#To prevent different vectors from converging to the same maxima,
#we use a "deflation" scheme of to decorrelate the outputs after every iteration
# - including the intialization step here:
for(p in 1:ncol(w)){
	if(p>1){
		sum = c(0,0,0)
		for(l in 1:(p-1)){
			sum = sum + t(w[p,])%*%w[l,]%*%w[l,]
		}
		w[p,] = w[p,] - sum
	} 
	w[p,] = w[p,]/sqrt(sum(w[p,]^2))
}

n.iters = 1000

#FastICA algo
for(i in 1:ncol(w)){
	for(f in 1:n.iters){
		
		#Step 2 of FastICA algo
		w[i,] = rowMeans(xwig*as.vector(g(t(w[i,])%*%xwig))) - mean(gprime(t(w[i,])%*%xwig))*w[i,] 
	
		#deflating
		if(i>1){
			sum = c(0,0,0)
			for(l in 1:(i-1)){
				sum = sum + t(w[i,])%*%w[l,]%*%w[l,]
			}
			w[i,] = w[i,] - sum
		} 
		#Normalizing w[i,] vector
		w[i,] = w[i,]/sqrt(sum(w[i,]^2))
		
	}
}

par(mfrow = c(1,3))

##Resulting components
s = w%*%xwig
plot(s[1,], type = "l")
plot(s[2,], type = "l")
plot(s[3,], type = "l")