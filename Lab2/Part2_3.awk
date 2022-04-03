BEGIN{
	FS = ","
	RS = "\n"

	count = 0
}
NR > 1{
	if($5 > $4){
		count++
	}
}
END{
	printf("The number of students that did better on exam 2 is %d\n", count)
}
