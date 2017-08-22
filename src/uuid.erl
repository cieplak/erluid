-module(uuid).

-export([generate/0, generate_base58/0, base58_decode/1, base58_encode/1]).

-on_load(init/0).

-define(APPNAME, uuid).
-define(LIBNAME, uuid).

init() ->
  SoName = case code:priv_dir(?APPNAME) of
             {error, bad_name} ->
               case filelib:is_dir(filename:join(["..", priv])) of
                 true ->
                   filename:join(["..", priv, ?LIBNAME]);
                 _ ->
                   filename:join([priv, ?LIBNAME])
               end;
             Dir ->
               filename:join(Dir, ?LIBNAME)
           end,
  erlang:load_nif(SoName, 0).

not_loaded(Line) ->
  exit({not_loaded, [{module, ?MODULE}, {line, Line}]}).

generate() ->
  exit(nif_library_not_loaded).

generate_base58() ->
  exit(nif_library_not_loaded).

base58_decode(_X) ->
  exit(nif_library_not_loaded).

base58_encode(_X) ->
  exit(nif_library_not_loaded).
