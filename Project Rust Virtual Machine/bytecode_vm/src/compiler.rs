


use std::collections::HashMap;
use crate::scanner::{Scanner, Token, TokenType};
use crate::{Chunk, OpCode, Value};



//parse function type used in pratt rules
type ParseFn = Option<fn(&mut Compiler)>;


//parserule
#[derive(Copy, Clone)]
pub struct ParseRule {
    pub prefix: ParseFn,
    pub infix: ParseFn,
    pub precedence: Precedence,
}

impl ParseRule {
    pub fn init_parse_rule(prefix: ParseFn, infix: ParseFn, precedence: Precedence) -> Self {
        Self { prefix, infix, precedence }
    }
}




//parser
pub struct Parser {
    pub current: Token,
    pub previous: Token,
    pub had_error: bool,
    pub panic_mode: bool,
    pub parse_rules: HashMap<TokenType, ParseRule>,
}

impl Parser {
    pub fn init_parser() -> Self {
        Self {
            current: Token {
                token_type: TokenType::TokenError,
                value: Vec::new(),
                length: 0,
                line: 0,
            },
            previous: Token {
                token_type: TokenType::TokenError,
                value: Vec::new(),
                length: 0,
                line: 0,
            },
            had_error: false,
            panic_mode: false,
            parse_rules: Parser::pratt_table(),
        }
    }

    //look up a rule by TokenType; fall back to (None, None, PrecNone).
    pub fn get_rule(&self, ttype: TokenType) -> ParseRule {
        let default = ParseRule::init_parse_rule(None, None, Precedence::PrecNone);
        *self.parse_rules.get(&ttype).unwrap_or(&default)
    }

    
    

    
    //pratt table mapping tokens to {prefix, infix, precedence}
    pub fn pratt_table() -> HashMap<TokenType, ParseRule> {
        let mut m: HashMap<TokenType, ParseRule> = HashMap::new();

        let grouping: ParseFn = Some(Compiler::grouping);
        let unary: ParseFn = Some(Compiler::unary);
        let binary: ParseFn = Some(Compiler::binary);
        let number: ParseFn = Some(Compiler::number);
        let literal: ParseFn = Some(Compiler::literal);
        let variable: ParseFn = Some(Compiler::variable);
        let none: ParseFn = None;
    

        // (key, {prefix, infix, precedence})
        m.insert(TokenType::TokenLeftParen,    ParseRule::init_parse_rule(grouping, none,   Precedence::PrecNone));
        m.insert(TokenType::TokenRightParen,   ParseRule::init_parse_rule(none,     none,   Precedence::PrecNone));
        m.insert(TokenType::TokenLeftBrace,    ParseRule::init_parse_rule(none,     none,   Precedence::PrecNone));
        m.insert(TokenType::TokenRightBrace,   ParseRule::init_parse_rule(none,     none,   Precedence::PrecNone));
        m.insert(TokenType::TokenComma,        ParseRule::init_parse_rule(none,     none,   Precedence::PrecNone));
        m.insert(TokenType::TokenDot,          ParseRule::init_parse_rule(none,     none,   Precedence::PrecNone));
        m.insert(TokenType::TokenMinus,        ParseRule::init_parse_rule(unary,    binary, Precedence::PrecTerm));
        m.insert(TokenType::TokenPlus,         ParseRule::init_parse_rule(none,     binary, Precedence::PrecTerm));
        m.insert(TokenType::TokenSemicolon,    ParseRule::init_parse_rule(none,     none,   Precedence::PrecTerm));
        m.insert(TokenType::TokenSlash,        ParseRule::init_parse_rule(none,     binary, Precedence::PrecFactor));
        m.insert(TokenType::TokenStar,         ParseRule::init_parse_rule(none,     binary, Precedence::PrecFactor));
        m.insert(TokenType::TokenNot,          ParseRule::init_parse_rule(none,     none,   Precedence::PrecFactor));
        m.insert(TokenType::TokenNotEqual,     ParseRule::init_parse_rule(none,     none,   Precedence::PrecFactor));
        m.insert(TokenType::TokenEqual,        ParseRule::init_parse_rule(none,     none,   Precedence::PrecFactor));
        m.insert(TokenType::TokenEqualEqual,   ParseRule::init_parse_rule(none,     none,   Precedence::PrecFactor));
        m.insert(TokenType::TokenGreater,      ParseRule::init_parse_rule(none,     none,   Precedence::PrecFactor));
        m.insert(TokenType::TokenGreaterEqual, ParseRule::init_parse_rule(none,     none,   Precedence::PrecFactor));
        m.insert(TokenType::TokenLess,         ParseRule::init_parse_rule(none,     none,   Precedence::PrecFactor));
        m.insert(TokenType::TokenLessEqual,    ParseRule::init_parse_rule(none,     none,   Precedence::PrecFactor));
        m.insert(TokenType::TokenIdentifier,   ParseRule::init_parse_rule(none,     none,   Precedence::PrecFactor));
        m.insert(TokenType::TokenString,       ParseRule::init_parse_rule(none,     none,   Precedence::PrecFactor));
        m.insert(TokenType::TokenNumber,       ParseRule::init_parse_rule(number,   none,   Precedence::PrecFactor));
        m.insert(TokenType::TokenAnd,          ParseRule::init_parse_rule(none,     none,   Precedence::PrecFactor));
        m.insert(TokenType::TokenClass,        ParseRule::init_parse_rule(none,     none,   Precedence::PrecFactor));
        m.insert(TokenType::TokenElse,         ParseRule::init_parse_rule(none,     none,   Precedence::PrecFactor));
        m.insert(TokenType::TokenFalse,        ParseRule::init_parse_rule(none,     none,   Precedence::PrecFactor));
        m.insert(TokenType::TokenFor,          ParseRule::init_parse_rule(none,     none,   Precedence::PrecFactor));
        m.insert(TokenType::TokenFun,          ParseRule::init_parse_rule(none,     none,   Precedence::PrecFactor));
        m.insert(TokenType::TokenIf,           ParseRule::init_parse_rule(none,     none,   Precedence::PrecFactor));
        m.insert(TokenType::TokenNil,          ParseRule::init_parse_rule(none,     none,   Precedence::PrecFactor));
        m.insert(TokenType::TokenOr,           ParseRule::init_parse_rule(none,     none,   Precedence::PrecFactor));
        m.insert(TokenType::TokenPrint,        ParseRule::init_parse_rule(none,     none,   Precedence::PrecFactor));
        m.insert(TokenType::TokenReturn,       ParseRule::init_parse_rule(none,     none,   Precedence::PrecFactor));
        m.insert(TokenType::TokenSuper,        ParseRule::init_parse_rule(none,     none,   Precedence::PrecFactor));
        m.insert(TokenType::TokenThis,         ParseRule::init_parse_rule(none,     none,   Precedence::PrecFactor));
        m.insert(TokenType::TokenTrue,         ParseRule::init_parse_rule(none,     none,   Precedence::PrecFactor));
        m.insert(TokenType::TokenVar,          ParseRule::init_parse_rule(none,     none,   Precedence::PrecFactor));
        m.insert(TokenType::TokenWhile,        ParseRule::init_parse_rule(none,     none,   Precedence::PrecFactor));
        m.insert(TokenType::TokenError,        ParseRule::init_parse_rule(none,     none,   Precedence::PrecFactor));
        m.insert(TokenType::TokenEof,          ParseRule::init_parse_rule(none,     none,   Precedence::PrecFactor));
        m.insert(TokenType::TokenNil,          ParseRule::init_parse_rule(literal, none,    Precedence::PrecNone));
        m.insert(TokenType::TokenFalse,        ParseRule::init_parse_rule(literal, none,    Precedence::PrecNone));
        m.insert(TokenType::TokenTrue,         ParseRule::init_parse_rule(literal, none,    Precedence::PrecNone));
        m.insert(TokenType::TokenNot,          ParseRule::init_parse_rule(unary, none,      Precedence::PrecNone));
        m.insert(TokenType::TokenNotEqual,     ParseRule::init_parse_rule(none, binary,     Precedence::PrecEquality));
        m.insert(TokenType::TokenEqualEqual,   ParseRule::init_parse_rule(none, binary,     Precedence::PrecEquality));
        m.insert(TokenType::TokenGreater,      ParseRule::init_parse_rule(none, binary,     Precedence::PrecComparison));
        m.insert(TokenType::TokenGreaterEqual, ParseRule::init_parse_rule(none, binary,     Precedence::PrecComparison));
        m.insert(TokenType::TokenLess,         ParseRule::init_parse_rule(none, binary,     Precedence::PrecComparison));
        m.insert(TokenType::TokenLessEqual,    ParseRule::init_parse_rule(none, binary,     Precedence::PrecComparison));
        m.insert(TokenType::TokenIdentifier,   ParseRule::init_parse_rule(variable, none,   Precedence::PrecNone));
        m
    }
}


//precedence
#[derive(Debug, Clone, Copy, PartialEq, Eq, PartialOrd, Ord)]
pub enum Precedence {
    PrecNone       = 0,
    PrecAssignment = 1,
    PrecOr         = 2,
    PrecAnd        = 3,
    PrecEquality   = 4,
    PrecComparison = 5,
    PrecTerm       = 6,
    PrecFactor     = 7,
    PrecUnary      = 8,
    PrecCall       = 9,
    PrecPrimary    = 10,
}

impl Precedence {
    pub fn from_integer(n: u32) -> Precedence {
        match n {
            0  => Precedence::PrecNone,
            1  => Precedence::PrecAssignment,
            2  => Precedence::PrecOr,
            3  => Precedence::PrecAnd,
            4  => Precedence::PrecEquality,
            5  => Precedence::PrecComparison,
            6  => Precedence::PrecTerm,
            7  => Precedence::PrecFactor,
            8  => Precedence::PrecUnary,
            9  => Precedence::PrecCall,
            10 => Precedence::PrecPrimary,
            _  => Precedence::PrecPrimary, // clamp
        }
    }
}

// Compiler
pub struct Compiler {
    pub chunk: Chunk,
    pub scanner: Scanner,
    pub parser: Parser,
}

impl Compiler {
    pub fn init_compiler() -> Compiler {
        Compiler {
            chunk: Chunk::init_chunk(),
            scanner: Scanner::init_scanner(""),
            parser: Parser::init_parser(),
        }
    }
    pub fn variable(&mut self) {
        
        let prev = self.parser.previous.clone();
        self.named_variable(prev);
    }

    pub fn named_variable(&mut self, token: Token) {
        let _name = String::from_utf8(token.value.clone()).unwrap_or_default();
        let index = self.identifier_constant(token);
        self.emit_bytes(OpCode::OpToBit(OpCode::OpGetGlobal), index);
    }
    pub fn get_chunk(&self) -> Chunk {
        self.chunk.clone()
    }

    fn match_tokentype(&mut self, token_type: TokenType) -> bool {
        if !self.check(token_type) {
            return false;
        }
        self.advance();
        true
    }
    pub fn check(&self, token_type: TokenType) -> bool {
        self.parser.current.token_type == token_type
    }
    fn parse_variable(&mut self, error_message: &str) -> u8 {
         // read the identifier token
    self.consume(TokenType::TokenIdentifier, error_message);

    //store the token in a local variable first
    let name_token = self.parser.previous.clone();

    // then turn it into a constant index
    self.identifier_constant(name_token)
    }

    pub fn identifier_constant(&mut self, name: Token) -> u8 {
    let s = String::from_utf8(name.value).unwrap_or_default();
    self.make_constant(Value::ValString(s))
}

    pub fn define_variable(&mut self, index: u8) {
        self.emit_bytes(OpCode::OpToBit(OpCode::OpDefineGlobal), index);
    }
    pub fn declaration(&mut self){
         // If we see 'var', parse a variable declaration.
        if self.match_tokentype(TokenType::TokenVar) {
            self.var_declaration();
        } else {
            // Otherwise, it's a normal statement.
            self.statement();
        }

        // Error recovery
        if self.parser.panic_mode {
            self.synchronize();
        }
    }

    pub fn var_declaration(&mut self){
        
        let index = self.parse_variable("Expect Variable Name");
        if self.match_tokentype(TokenType::TokenEqual) {
            self.expression();
        }else{
            self.emit_byte(OpCode::OpNil as u8);
        }
        self.consume(TokenType::TokenSemicolon, ";");
        self.define_variable(index);

    }
     fn synchronize(self: &mut Compiler) {
            self.parser.panic_mode = false;
            while self.parser.current.token_type != TokenType::TokenEof {
                if self.parser.previous.token_type == TokenType::TokenSemicolon {
                    return;
                }

                match self.parser.current.token_type {
                    TokenType::TokenClass  => return,
                    TokenType::TokenFun    => return,
                    TokenType::TokenVar    => return,
                    TokenType::TokenFor    => return,
                    TokenType::TokenIf     => return,
                    TokenType::TokenWhile  => return,
                    TokenType::TokenPrint  => return,
                    TokenType::TokenReturn => return,
                    _ => break,
                }
                self.advance();
            }
        }
    pub fn statement(&mut self){
         if self.match_tokentype(TokenType::TokenPrint) {
        self.print_statement();
        } else {
            self.expression_statement();
           
    }
    
    }
    fn expression_statement(&mut self) {
        self.expression();
        self.consume(TokenType::TokenSemicolon, "Expect ';' after expression.");
        self.emit_byte(OpCode::OpToBit(OpCode::OpPop));
    }

    fn print_statement(&mut self) {
        self.expression();
        self.consume(TokenType::TokenSemicolon, "Expect ';' after value.");
        self.emit_byte(OpCode::OpToBit(OpCode::OpPrint));
    }

    pub fn literal(&mut self) {
    match self.parser.previous.token_type {
        TokenType::TokenNil => self.emit_byte(OpCode::OpNil as u8),
        TokenType::TokenFalse => self.emit_byte(OpCode::OpFalse as u8),
        TokenType::TokenTrue => self.emit_byte(OpCode::OpTrue as u8),
        _ => {}
        }
    }   
    //compile pipeline
    pub fn compile(&mut self, source_code: &str) -> bool {
        // 1. init scanner
        self.scanner = Scanner::init_scanner(source_code);
        // 2. advance
        self.advance();
        // 3. expression
        while !self.match_tokentype( TokenType::TokenEof) {
            self.declaration();
        }
        // self.expression();
        // // 4. consume EOF
        // self.consume(TokenType::TokenEof, "Expect end of expression.");
        // // 5.end_compiler
        self.end_compiler();
        // 6. return success
        !self.parser.had_error
    }

//parsing helpers
    pub fn advance(&mut self) {
        self.parser.previous = self.parser.current.clone();

        loop {
            let token = self.scanner.scan_token();
            self.parser.current = token.clone();

            if self.parser.current.token_type != TokenType::TokenError {
                break;
            }

            let msg = String::from_utf8(token.value).unwrap_or_else(|_| "Scan error".to_string());
            self.error_at_current(&msg);
        }
    }

    pub fn consume(&mut self, ttype: TokenType, message: &str) {
        if self.parser.current.token_type == ttype {
            self.advance();
            return;
        }
        self.error_at_current(message);
    }

    pub fn expression(&mut self) {
        self.parse_precedence(Precedence::PrecAssignment);
    }

    pub fn grouping(&mut self) {
        self.expression();
        self.consume(TokenType::TokenRightParen, "Expect ')' after expression.");
    }

    pub fn unary(&mut self) {
        let operator_type = self.parser.previous.token_type;
        self.parse_precedence(Precedence::PrecUnary);
        match operator_type {
            TokenType::TokenMinus => self.emit_byte(OpCode::OpToBit(OpCode::OpNegate)),
            TokenType::TokenNot => self.emit_byte(OpCode::OpNot as u8),
            _ => { /* '!' not implemented in this assignment */ }
        }
       
    }

    pub fn number(&mut self) {
        let lexeme = String::from_utf8(self.parser.previous.value.clone()).unwrap_or_default();
        
        match lexeme.parse::<i16>() {
            Ok(v) => self.emit_constant(Value::ValNumber(v)),
            Err(_) => self.error("Invalid number literal."),
        }
    }

    pub fn binary(&mut self) {
        let operator_type = self.parser.previous.token_type;

        let rule = self.parser.get_rule(operator_type);
        let higher = Precedence::from_integer((rule.precedence as u32) + 1);
        self.parse_precedence(higher);

        match operator_type {
             TokenType::TokenPlus  => self.emit_byte(OpCode::OpToBit(OpCode::OpAdd)),
            TokenType::TokenMinus => self.emit_byte(OpCode::OpToBit(OpCode::OpSubtract)),
            TokenType::TokenStar  => self.emit_byte(OpCode::OpToBit(OpCode::OpMultiply)),
            TokenType::TokenSlash => self.emit_byte(OpCode::OpToBit(OpCode::OpDivide)),

            // equality
            TokenType::TokenEqualEqual => {
                self.emit_byte(OpCode::OpToBit(OpCode::OpEqual));
            }
            TokenType::TokenNotEqual => {
                // !(a == b)
                self.emit_byte(OpCode::OpToBit(OpCode::OpEqual));
                self.emit_byte(OpCode::OpToBit(OpCode::OpNot));
            }

            // comparisons
            TokenType::TokenGreater => {
                self.emit_byte(OpCode::OpToBit(OpCode::OpGreater));
            }
            TokenType::TokenGreaterEqual => {
                // !(a < b)
                self.emit_byte(OpCode::OpToBit(OpCode::OpLess));
                self.emit_byte(OpCode::OpToBit(OpCode::OpNot));
            }
            TokenType::TokenLess => {
                self.emit_byte(OpCode::OpToBit(OpCode::OpLess));
            }
            TokenType::TokenLessEqual => {
                // !(a > b)
                self.emit_byte(OpCode::OpToBit(OpCode::OpGreater));
                self.emit_byte(OpCode::OpToBit(OpCode::OpNot));
            }

            _ => {}
        }
    }

    pub fn parse_precedence(&mut self, precedence: Precedence) {
        self.advance();

        // prefix
        let prefix_rule = self.parser.get_rule(self.parser.previous.token_type).prefix;
        match prefix_rule {
            Some(func) => func(self),
            None => panic!("Expected Expression"),
        }

        // infix (while next has >= precedence)
        loop {
            let current_rule = self.parser.get_rule(self.parser.current.token_type);
            if precedence > current_rule.precedence {
                break;
            }
            // if there's no infix handler for this token, don't consume it
            if current_rule.infix.is_none() {
                return;
            }
            // consume the infix operator and call its handler
            self.advance();
            match current_rule.infix {
                Some(func) => func(self),
                None => return,
            }
        }
    }

//emit helpers
    pub fn emit_byte(&mut self, byte: u8) {
        let line = self.parser.previous.line as u32;
        self.chunk.write_to_chunk(byte, line);
    }

    pub fn emit_bytes(&mut self, b1: u8, b2: u8) {
        self.emit_byte(b1);
        self.emit_byte(b2);
    }

    pub fn emit_return(&mut self) {
        self.emit_byte(OpCode::OpToBit(OpCode::OpReturn));
    }

    pub fn make_constant(&mut self, value: Value) -> u8 {
        self.chunk.add_constant(value)
    }

    pub fn emit_constant(&mut self, value: Value) {
        let idx = self.make_constant(value);
        self.emit_bytes(OpCode::OpToBit(OpCode::OpConstant), idx);
    }

    pub fn end_compiler(&mut self) {
        self.emit_return();
    }





//errors
    pub fn error_at_current(&mut self, message: &str) {
        self.error_at(self.parser.current.clone(), message);
    }

    pub fn error(&mut self, message: &str) {
        self.error_at(self.parser.previous.clone(), message);
    }

    pub fn error_at(&mut self, token: Token, message: &str) {
        if self.parser.panic_mode {
            return;
        }
        self.parser.panic_mode = true;
        println!("[line {}] Error", token.line);
        if token.token_type == TokenType::TokenEof {
            println!(" at end");
        } else {
            if token.token_type == TokenType::TokenError {
                // nothing
            } else {
                println!(" at {} {:?}", token.length, token);
            }
        }
        println!(": {}\n", message);
        self.parser.had_error = true;
    }

    
}
    