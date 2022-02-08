# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/08 07:03:11 by jodufour          #+#    #+#              #
#    Updated: 2022/02/08 14:22:53 by jodufour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

######################################
#              COMMANDS              #
######################################
CC		=	clang -c
LINK	=	clang
MKDIR	=	mkdir -p
RM		=	rm -rf

######################################
#             EXECUTABLE             #
######################################
NAME	=	microshell.out

#######################################
#             DIRECTORIES             #
#######################################
SRC_DIR	=	srcs/
OBJ_DIR	=	objs/
PRV_DIR	=	private/

######################################
#            SOURCE FILES            #
######################################
SRC		=	\
			cd.c					\
			exec.c					\
			main.c					\
			pipeline.c				\
			redirect.c

######################################
#            OBJECT FILES            #
######################################
OBJ		=	${SRC:.c=.o}
OBJ		:=	${addprefix ${OBJ_DIR}, ${OBJ}}

DEP		=	${OBJ:.o=.d}

#######################################
#                FLAGS                #
#######################################
CFLAGS	=	-Wall -Wextra #-Werror
CFLAGS	+=	-MMD -MP
CFLAGS	+=	-I${PRV_DIR}

LDFLAGS	=	

ifeq (${DEBUG}, 1)
	CFLAGS	+=	-g
endif

#######################################
#                RULES                #
#######################################
${NAME}: ${OBJ}
	${LINK} ${OBJ} ${LDFLAGS} ${OUTPUT_OPTION}

all: ${NAME}

-include ${DEP}

${OBJ_DIR}%.o: ${SRC_DIR}%.c
	@${MKDIR} ${@D}
	${CC} ${CFLAGS} $< ${OUTPUT_OPTION}

clean:
	${RM} ${OBJ_DIR} ${NAME} vgcore.*

fclean:
	${RM} ${OBJ_DIR} ${NAME} vgcore.*

re: clean all

fre: fclean all

-include /home/jodufour/Templates/mk_files/coffee.mk
-include /home/jodufour/Templates/mk_files/norm.mk

.PHONY: all clean fclean re fre
