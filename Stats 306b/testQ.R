error = array()


for(q in 1:20){

#initialize the imputed matrix with column means
imputed.xo = xo

for(i in 1:nrow(xo)){
	for(j in 1:ncol(xo)){
		if(is.na(xo[i,j])){
			imputed.xo[i,j] = mean(xo[,j], na.rm = TRUE)
		}
	}
}

#imputing...


difference = array()
iter = 1
d = array(0, dim = 100)
d[1:q] = 1

while(TRUE){
	
#calculate svd of matrix with imputed values
svd.imputed = svd(imputed.xo)

#make matrix approximation with rank q

approx.xo = svd.imputed$u%*%diag(d*svd.imputed$d)%*%t(svd.imputed$v)

newImputed.xo = ifelse(is.na(xo), approx.xo, xo)

difference = norm(imputed.xo - newImputed.xo)/norm(imputed.xo)
print(difference[iter])



if(difference < 10^-3){break}
imputed.xo = newImputed.xo	
}
error[q] = sum(abs(xc-newImputed.xo), na.rm = TRUE)/sum(!is.na(xc), na.rm = TRUE)
}