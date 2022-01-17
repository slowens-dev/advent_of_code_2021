def settings(**kwargs):
    return {
            'flags':[
                '-Wall -Werror',
                'std=c99 -xc',
                '-I./src/headers/',
                ]
            }
