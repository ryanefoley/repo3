p = array()
for(i in 1:nrow(micro)){
	p[i] = t.test(micro[i,1:20], micro[i,21:40])$p.value
}
