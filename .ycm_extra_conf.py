def Settings(** kwargs):
    return {
            'flags': [ 
                        '-Wall', 
                        '-Wextra',
                        '-Werror',
                        '-xc', 
                        'I./src/headers/',
                     ],
            }
