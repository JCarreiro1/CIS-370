
BEGIN{

	FS = ","

	RS = "\n"

	group1 = 0
	group2 = 0
	group3 = 0

}
NR > 1 {

	if($3 == 1){
		group1++
	} else if($3 == 2){
		group2++
	} else{
		group3++
	}

}
END{
	printf("There are %d students in group 1\n", group1)
	printf("There are %d students in group 2\n", group2)
	printf("There are %d students in group 3\n", group3)
}
