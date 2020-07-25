src_dir = '../src'

unity_dep = dependency('unity',
    fallback : ['unity', 'unity_dep']
)

test('lexer',
    executable('test_lexer',
        ['test_lexer.c', src_dir + '/lexer.c', src_dir + '/token.c'],
        dependencies: unity_dep
    )
)
