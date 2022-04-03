BEGIN{
	FS = ","
	RS = "\n"

	scores = 0
}
NR > 1{
	score += $5
}
END{
	score /= 20
	
	printf("The average score for exam 2 is %f\n", score)
}
