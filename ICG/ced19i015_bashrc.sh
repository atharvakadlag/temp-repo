alias cdced="cd /home/user/ced19i015"
alias vv='eval $(history -p !vim)'

rungl () {
	fname=$1
	g++ $fname -lGL -lGLU -lglut -lGLEW -o ${fname%.cpp} && ./${fname%.cpp}
}
