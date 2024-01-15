# kyusulib
My C Library For 42Seoul


## Compile
```bash
$ make
```

## Use
 - Include this lib into project that will use the libraries of kyusulib
 - Include kyusulib.h
 - Write libkyusulib.a at project Makefile to compile

```Makefile
$(NAME)		:	$(OBJS) $(KYUSULIB_A)
				@$(CC) $(CFLAGS) -include$(HEAD) -L$(KYUSULIB) -lkysulib $(OBJS) -o $(NAME)
				@$(ECHO) "*** Linking complete."
```
## Etc
.
