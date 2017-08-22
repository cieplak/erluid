INCLUDES = -I . -I /usr/local/include -I /usr/local/lib/erlang/usr/include

default: uuid_nif

uuid_nif:
	c++ -std=c++1z $(INCLUDES)  uuid_nif.cpp -fpic -shared -o uuid.so && cp uuid.so ../priv/.
