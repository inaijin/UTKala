CC_EXEC=g++
CC_FLAGS=-std=c++11

CC= ${CC_EXEC} ${CC_FLAGS}

BUILD_DIR=build

executable: ${BUILD_DIR}/account.o ${BUILD_DIR}/person.o ${BUILD_DIR}/signup.o ${BUILD_DIR}/utilities.o ${BUILD_DIR}/signin.o ${BUILD_DIR}/post.o ${BUILD_DIR}/getdel.o ${BUILD_DIR}/handelers.o ${BUILD_DIR}/main.o
	${CC_EXEC} ${BUILD_DIR}/account.o ${BUILD_DIR}/person.o ${BUILD_DIR}/signup.o ${BUILD_DIR}/utilities.o ${BUILD_DIR}/signin.o ${BUILD_DIR}/post.o ${BUILD_DIR}/getdel.o ${BUILD_DIR}/handelers.o ${BUILD_DIR}/request.o ${BUILD_DIR}/response.o ${BUILD_DIR}/route.o ${BUILD_DIR}/server.o ${BUILD_DIR}/template_parser.o ${BUILD_DIR}/utilitiess.o ${BUILD_DIR}/main.o -o utkala.out

${BUILD_DIR}/main.o: main.cpp account.hpp person.hpp signup.hpp signin.hpp post.hpp getdel.hpp handelers.hpp
	${CC} -c main.cpp -o ${BUILD_DIR}/main.o

${BUILD_DIR}/person.o: person.cpp person.hpp
	${CC} -c person.cpp -o ${BUILD_DIR}/person.o

${BUILD_DIR}/account.o: account.cpp account.hpp person.hpp
	${CC} -c account.cpp -o ${BUILD_DIR}/account.o

${BUILD_DIR}/signup.o: signup.cpp signup.hpp account.hpp utilities.hpp
	${CC} -c signup.cpp -o ${BUILD_DIR}/signup.o

${BUILD_DIR}/utilities.o: utilities.cpp utilities.hpp account.hpp person.hpp
	${CC} -c utilities.cpp -o ${BUILD_DIR}/utilities.o

${BUILD_DIR}/signin.o: signin.cpp signin.hpp account.hpp
	${CC} -c signin.cpp -o ${BUILD_DIR}/signin.o

${BUILD_DIR}/post.o: post.cpp post.hpp account.hpp signin.hpp signup.hpp utilities.hpp
	${CC} -c post.cpp -o ${BUILD_DIR}/post.o

${BUILD_DIR}/getdel.o: getdel.cpp getdel.hpp account.hpp
	${CC} -c getdel.cpp -o ${BUILD_DIR}/getdel.o

${BUILD_DIR}/handelers.o: handelers.cpp handelers.hpp account.hpp utilities.hpp
	${CC} -c handelers.cpp -o ${BUILD_DIR}/handelers.o

clean:
	rm -rf ${BUILD_DIR} && mkdir -p ${BUILD_DIR}