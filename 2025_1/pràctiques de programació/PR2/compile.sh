#!/bin/zsh

rm -rf build/*.o bin/UOC20251d lib/NetUOCd.a

gcc -g -c NetUOC/src/api.c -o build/api.o -I NetUOC/include
gcc -g -c NetUOC/src/company.c -o build/company.o -I NetUOC/include
gcc -g -c NetUOC/src/csv.c -o build/csv.o -I NetUOC/include
gcc -g -c NetUOC/src/date.c -o build/date.o -I NetUOC/include
gcc -g -c NetUOC/src/job.c -o build/job.o -I NetUOC/include
gcc -g -c NetUOC/src/person.c -o build/person.o -I NetUOC/include
gcc -g -c NetUOC/src/application.c -o build/application.o -I NetUOC/include

# Compilar main.c
gcc -g -c src/main.c -o build/main_app.o -I NetUOC/include -I test/include

# Compilar test_suite.c
gcc -g -c test/src/test_suite.c -o build/test_suite.o -I NetUOC/include -I test/include

# Compilar test.c (utilidades como parseArguments/waitKey)
gcc -g -c test/src/test.c -o build/test_utils.o -I NetUOC/include -I test/include

# Compilar test_pr1.c (lógica de las pruebas)
gcc -g -c test/src/test_pr2.c -o build/test_pr2.o -I NetUOC/include -I test/include
gcc -g -c test/src/test_pr1.c -o build/test_pr1.o -I NetUOC/include -I test/include
ar rcs lib/libNetUOCd.a build/*.o

gcc -Wall -Wextra -g -fsanitize=address build/*.o -o bin/UOC20251d -L lib -lNetUOCd

# Ejecutar el binario generado
./bin/UOC20251d
