#	$OpenBSD$

HTTPDSRC =	${.CURDIR}/../../httpd

.PATH:	${HTTPDSRC}

REGRESS_TARGETS=	test-patterns

CLEANFILES +=		patterns-tester

patterns-tester: patterns-tester.c patterns.c patterns.h
	${CC} -o $@ ${CFLAGS} ${.CURDIR}/patterns-tester.c ${HTTPDSRC}/patterns.c -I${HTTPDSRC}

test-patterns: patterns-tester test-patterns.out test-patterns.in
	cat ${.CURDIR}/test-patterns.in | grep -v '^#' |			\
	while IFS='	' read string pattern comments ; do 			\
		./patterns-tester "$${string}" "$${pattern}" 2>&1 || true;	\
	done | diff -I 'OpenBSD' -u ${.CURDIR}/test-patterns.out -

.include <bsd.regress.mk>
