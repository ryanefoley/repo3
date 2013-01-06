x = mvrnorm(n = 3, mu = rep(0,1000), Sigma = diag(rep(2, 1000)) + matrix(1, ncol = 1000, nrow = 1000))
y = matrix(rnorm(3), ncol = 1)

x.svd = prcomp(x, retx=TRUE, center=TRUE)

u = x.svd$x
d = diag(x.svd$sdev)
v = x.svd$rotation

z = u%*%d
lambda = 2;
i = diag(rep(1,3))
betaZ = solve(t(z) %*% z + lambda * i) %*% t(z) %*% y
betaX = v %*% betaZ

k = x %*% t(x)
yhat = solve(lambda*i + k) %*% k %*% y

yTrick = x %*% betaX

abs(yhat-yTrick)


