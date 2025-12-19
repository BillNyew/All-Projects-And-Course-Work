
#[derive(Debug, Copy, Clone, PartialEq, Eq, Hash)]
pub enum TokenType {
    TokenLeftParen, TokenRightParen,
    TokenLeftBrace, TokenRightBrace,
    TokenComma,
    TokenDot,
    TokenSemicolon,
    TokenMinus, TokenPlus,
    TokenSlash, TokenStar,
    TokenNot, TokenNotEqual,
    TokenEqual, TokenEqualEqual,
    TokenLess, TokenLessEqual,
    TokenGreater, TokenGreaterEqual,
    TokenIdentifier,
    TokenString,
    TokenNumber,
    TokenTrue, TokenFalse,
    TokenAnd, TokenOr,
    TokenIf, TokenElse,
    TokenClass, TokenSuper, TokenThis,
    TokenFun,
    TokenVar,
    TokenReturn,
    TokenFor,
    TokenWhile,
    TokenNil,
    TokenPrint,
    TokenError,
    TokenEof,
}

#[derive(Debug, Clone)]
pub struct Token {
    pub token_type: TokenType,
    pub value: Vec<u8>,  // bytes [start..current]
    pub length: usize,   // value.len()
    pub line: usize,
}

#[derive(Debug, Clone)]
pub struct Scanner {
    source_code: Vec<u8>,
    start_index: usize,
    current_index: usize,
    line_number: usize,
}

impl Scanner {
    pub fn init_scanner(sc: &str) -> Self {
        Self {
            source_code: sc.as_bytes().to_vec(),
            start_index: 0,
            current_index: 0,
            line_number: 1,
        }
    }

    #[inline]
    fn is_at_end(&self) -> bool {
        self.current_index >= self.source_code.len()
    }

    #[inline]
    fn peek(&self) -> u8 {
        if self.is_at_end() { b'\0' } else { self.source_code[self.current_index] }
    }

    #[inline]
    fn peek_next(&self) -> u8 {
        if self.current_index + 1 >= self.source_code.len() { b'\0' } else { self.source_code[self.current_index + 1] }
    }

    #[inline]
    fn advance(&mut self) -> u8 {
        let c = self.peek();
        if !self.is_at_end() {
            self.current_index += 1;
        }
        c
    }

    #[inline]
    fn skip_next_character(&mut self) {
        if !self.is_at_end() {
            self.current_index += 1;
        }
    }

    fn skip_whitespace(&mut self) {
        loop {
            match self.peek() {
                b' ' | b'\r' | b'\t' => { self.advance(); }
                b'\n' => { self.advance(); self.line_number += 1; }
                b'/' if self.peek_next() == b'/' => {
                    // comment: skip until end of line
                    while self.peek() != b'\n' && !self.is_at_end() { self.advance(); }
                }
                _ => break,
            }
        }
    }

    #[inline]
    fn match_next(&mut self, expected: u8) -> bool {
        if self.is_at_end() { return false; }
        if self.source_code[self.current_index] != expected { return false; }
        self.current_index += 1;
        true
    }

    fn make_token(&self, token_type: TokenType) -> Token {
        let value = self.source_code[self.start_index..self.current_index].to_vec();
        Token {
            token_type,
            length: value.len(),
            value,
            line: self.line_number,
        }
    }

    fn error_token(&self, message: &str) -> Token {
        let value = message.as_bytes().to_vec();
        Token {
            token_type: TokenType::TokenError,
            length: value.len(),
            value,
            line: self.line_number,
        }
    }

    fn get_literal_string(&mut self) -> Token {
        while self.peek() != b'"' && !self.is_at_end() {
            if self.peek() == b'\n' {
                self.line_number += 1;
            }
            self.advance();
        }
        if self.is_at_end() {
            return self.error_token("Unterminated String Literal");
        }
        // consume closing quote
        self.advance();
        self.make_token(TokenType::TokenString)
    }

    fn get_literal_number(&mut self) -> Token {
        while is_digit(self.peek()) { self.advance(); }
        if self.peek() == b'.' && is_digit(self.peek_next()) {
            self.advance(); // '.'
            while is_digit(self.peek()) { self.advance(); }
        }
        self.make_token(TokenType::TokenNumber)
    }

    fn get_identifier(&mut self) -> Token {
        while is_alpha(self.peek()) || is_digit(self.peek()) { self.advance(); }
        let ttype = self.identifier_type(); // optional keyword recognition
        self.make_token(ttype)
    }

    fn identifier_type(&self) -> TokenType {
        let lex = &self.source_code[self.start_index..self.current_index];
        match lex {
            b"and"    => TokenType::TokenAnd,
            b"class"  => TokenType::TokenClass,
            b"else"   => TokenType::TokenElse,
            b"false"  => TokenType::TokenFalse,
            b"for"    => TokenType::TokenFor,
            b"fun"    => TokenType::TokenFun,
            b"if"     => TokenType::TokenIf,
            b"nil"    => TokenType::TokenNil,
            b"or"     => TokenType::TokenOr,
            b"print"  => TokenType::TokenPrint,
            b"return" => TokenType::TokenReturn,
            b"super"  => TokenType::TokenSuper,
            b"this"   => TokenType::TokenThis,
            b"true"   => TokenType::TokenTrue,
            b"var"    => TokenType::TokenVar,
            b"while"  => TokenType::TokenWhile,
            _ => TokenType::TokenIdentifier,
        }
    }

    pub fn scan_token(&mut self) -> Token {
        self.skip_whitespace();
        self.start_index = self.current_index;

        if self.is_at_end() {
            return self.make_token(TokenType::TokenEof);
        }

        let c = self.advance();

        if is_alpha(c) {
            return self.get_identifier();
        }
        if is_digit(c) {
            return self.get_literal_number();
        }

        match c {
            b'(' => self.make_token(TokenType::TokenLeftParen),
            b')' => self.make_token(TokenType::TokenRightParen),
            b'{' => self.make_token(TokenType::TokenLeftBrace),
            b'}' => self.make_token(TokenType::TokenRightBrace),
            b';' => self.make_token(TokenType::TokenSemicolon),
            b',' => self.make_token(TokenType::TokenComma),
            b'.' => self.make_token(TokenType::TokenDot),
            b'+' => self.make_token(TokenType::TokenPlus),
            b'-' => self.make_token(TokenType::TokenMinus),
            b'*' => self.make_token(TokenType::TokenStar),
            b'/' => self.make_token(TokenType::TokenSlash),

            b'!' => if self.match_next(b'=') {
                self.make_token(TokenType::TokenNotEqual)
            } else {
                self.make_token(TokenType::TokenNot)
            },
            b'=' => if self.match_next(b'=') {
                self.make_token(TokenType::TokenEqualEqual)
            } else {
                self.make_token(TokenType::TokenEqual)
            },
            b'<' => if self.match_next(b'=') {
                self.make_token(TokenType::TokenLessEqual)
            } else {
                self.make_token(TokenType::TokenLess)
            },
            b'>' => if self.match_next(b'=') {
                self.make_token(TokenType::TokenGreaterEqual)
            } else {
                self.make_token(TokenType::TokenGreater)
            },

            b'"' => self.get_literal_string(),
            _ => self.error_token("Unknown character."),
        }
    }
}

// helpers
#[inline]
fn is_digit(c: u8) -> bool {
    (c as char).is_ascii_digit()
}
#[inline]
fn is_alpha(c: u8) -> bool {
    (c as char).is_ascii_alphabetic() || c == b'_'
}
