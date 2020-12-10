cmake_minimum_required(VERSION 3.16)
project(minishell)

set(CMAKE_CXX_STANDARD 14)

ADD_COMPILE_OPTIONS(-Wall -Wextra -Werror)
include_directories(inc)
include_directories(libft)

add_executable(minishell
    inc/minishell.h
   libft/Makefile
        srcs/validate.c
        srcs/free.c
        srcs/parse_env.c
        srcs/parse_proc.c
        srcs/parse_quote.c
        srcs/parse_utils.c
        srcs/parse_env2.c
        srcs/main.c
        srcs/export.c
        srcs/utils.c
        srcs/pipe.c
        srcs/parse.c
        srcs/unset.c
        srcs/redirect.c
        srcs/pwd.c
        srcs/get_next_line.c
        srcs/get_next_line_utils.c
        srcs/env.c
        srcs/echo.c
        srcs/chdir.c
        srcs/init.c srcs/exit.c)

add_library(ft STATIC
        libft/ft_atoi.c
        libft/ft_bzero.c
        libft/ft_calloc.c
        libft/ft_free.c
        libft/ft_free_mat.c
        libft/ft_isalnum.c
        libft/ft_isalpha.c
        libft/ft_isascii.c
        libft/ft_isdigit.c
        libft/ft_isprint.c
        libft/ft_itoa.c
        libft/ft_lstadd_back.c
        libft/ft_lstadd_front.c
        libft/ft_lstclear.c
        libft/ft_lstdelone.c
        libft/ft_lstiter.c
        libft/ft_lstlast.c
        libft/ft_lstmap.c
        libft/ft_lstnew.c
        libft/ft_lstsize.c
        libft/ft_matdup.c
        libft/ft_matjoin.c
        libft/ft_matrow.c
        libft/ft_memccpy.c
        libft/ft_memchr.c
        libft/ft_memcmp.c
        libft/ft_memcpy.c
        libft/ft_iswhite.c
        libft/ft_memmove.c
        libft/ft_memset.c
        libft/ft_putchar_fd.c
        libft/ft_putendl_fd.c
        libft/ft_putnbr_fd.c
        libft/ft_putstr_fd.c
        libft/ft_split.c
        libft/ft_strccmp.c
        libft/ft_strchr.c
        libft/ft_strcjoin.c
        libft/ft_strdup.c
        libft/ft_strjoin.c
        libft/ft_strlcat.c
        libft/ft_strlcpy.c
        libft/ft_strlen.c
        libft/ft_strmapi.c
        libft/ft_strncmp.c
        libft/ft_strnstr.c
        libft/ft_strrchr.c
        libft/ft_strtrim.c
        libft/ft_substr.c
        libft/ft_tolower.c
        libft/ft_toupper.c
        libft/ft_write.c
        libft/libft.h)
target_link_libraries(minishell ft)
