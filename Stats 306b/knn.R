absError = array()
m = xo
cor.m = cor(t(m), use = "pairwise.complete.obs")

for(k in 1:10){
m = xo

for(i in 1:nrow(m)){
	rowsSorted = sort(cor.m[i,-i], decreasing = TRUE, method = c("quick"), index.return = TRUE)
	for(j in 1:ncol(m)){
		if(is.na(m[i,j])){			
			q = 1
			z = 1
			values = array()
			while(q<=k){
				if(z>length(rowsSorted$ix)){break}
				if(!is.na(m[rowsSorted$ix[z],j])){
					values[q] = m[rowsSorted$ix[z],j]
					q = q+1
					if(q>k){break}
				}
				z = z+1
			}
			m[i,j] = mean(values)
		}
	}
}
absError[k] = sum(abs(na.omit(xc-m)), rm.na = TRUE)
}
