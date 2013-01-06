s = 1:200
x1 = 10*s - 5
x2 = .5*s + 10
x3 = -3*s -5
x = cbind(x1,x2,x3)
y = s

k = x%*%t(x)

n = 200
i = diag(rep(1, 200))
lambda = 2

ya = x%*%solve((t(x)%*%x + lambda*diag(rep(1,3)))) %*% t(x) %*% y
yb = solve(k+lambda*i) %*% k %*% y
