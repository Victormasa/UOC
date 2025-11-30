#!/bin/zsh

rm -rf build/*.o UOC20251/bin/UOC20251d UOC20251/lib/NetUOCd.a NetUOC/lib/libNetUOC.a

gcc -g -c NetUOC/src/api.c -o build/api.o -I NetUOC/include
gcc -g -c NetUOC/src/company.c -o build/company.o -I NetUOC/include
gcc -g -c NetUOC/src/csv.c -o build/csv.o -I NetUOC/include
gcc -g -c NetUOC/src/date.c -o build/date.o -I NetUOC/include
gcc -g -c NetUOC/src/job.c -o build/job.o -I NetUOC/include
gcc -g -c NetUOC/src/person.c -o build/person.o -I NetUOC/include

# Usamos -I NetUOC/include y -I UOC20251/test/include para encontrar TODOS los headers necesarios.
# (Hemos asumido que el archivo 'test.c' contiene las utilidades y lo llamaremos 'test_utils.o')

# Compilar main.c
gcc -g -c UOC20251/src/main.c -o build/main_app.o -I NetUOC/include -I UOC20251/test/include

# Compilar test_suite.c
gcc -g -c UOC20251/test/src/test_suite.c -o build/test_suite.o -I NetUOC/include -I UOC20251/test/include

# Compilar test.c (utilidades como parseArguments/waitKey)
gcc -g -c UOC20251/test/src/test.c -o build/test_utils.o -I NetUOC/include -I UOC20251/test/include

# Compilar test_pr1.c (lógica de las pruebas)
gcc -g -c UOC20251/test/src/test_pr1.c -o build/test_pr1.o -I NetUOC/include -I UOC20251/test/include

ar rcs NetUOC/lib/libNetUOCd.a build/*.o

gcc -Wall -Wextra -g -fsanitize=address build/*.o -o UOC20251/bin/UOC20251d -L NetUOC/lib -lNetUOCd

# Ejecutar el binario generado
./UOC20251/bin/UOC20251d
