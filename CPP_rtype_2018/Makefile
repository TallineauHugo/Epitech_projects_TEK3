all: Server Client

Server:
	make -C ./Server/

Client:
	make -C ./Client/

Rtype:
	make -C ./Rtype/

clean:
	make -C ./Server/ clean
	make -C ./Client/ clean

fclean:
	make -C ./Server/ fclean
	make -C ./Client/ fclean

re:	fclean all

.PHONY: all Server Client clean fclean re
