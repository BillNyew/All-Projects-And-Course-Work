pub mod scanner;
pub mod compiler; 
use crate::compiler::Compiler;
use scanner::{Scanner, TokenType};
use std::collections::HashMap;


//pub type Value = i16;
pub type Number = i16;
#[derive(Debug, Clone, PartialEq, Eq)]
// removed copy due to ValString
pub enum Value{
    ValBool(bool),
    ValNumber(Number),
    ValNil,
    ValString(String)
}

#[derive(Debug, Copy, Clone, PartialEq, Eq)] //note to group - bro why do we even have modulo it was in the directions to add it but never to actually implement it, unless we're stupid
pub enum OpCode {
    OpReturn,
    OpConstant,
    OpNegate,
    OpAdd,
    OpSubtract,
    OpMultiply,
    OpDivide,
    OpModulo,
    OpNil,
    OpTrue,
    OpFalse,
    OpNot,
    OpEqual,
    OpGreater,
    OpLess,
    OpPrint,
    OpPop,
    OpDefineGlobal,
    OpGetGlobal
}

impl OpCode {
    pub fn OpToBit(name: OpCode) -> u8 {
        match name {
            OpCode::OpReturn   => 0,
            OpCode::OpConstant => 1,
            OpCode::OpNegate   => 2,
            OpCode::OpAdd      => 3,
            OpCode::OpSubtract => 4,
            OpCode::OpMultiply => 5,
            OpCode::OpDivide   => 6,
            OpCode::OpModulo   => 7,
            OpCode::OpNil      => 8,
            OpCode::OpTrue     => 9,
            OpCode::OpFalse    => 10,
            OpCode::OpNot      => 11,
            OpCode::OpEqual    => 12,
            OpCode::OpGreater  => 13,
            OpCode::OpLess     => 14,
            OpCode::OpPrint    => 15,
            OpCode::OpPop      => 16,
            OpCode::OpDefineGlobal => 17,
            OpCode::OpGetGlobal => 18
        }
    }

    pub fn BitToOp(num: u8) -> OpCode {
        match num {
            0 => OpCode::OpReturn,
            1 => OpCode::OpConstant,
            2 => OpCode::OpNegate,
            3 => OpCode::OpAdd,
            4 => OpCode::OpSubtract,
            5 => OpCode::OpMultiply,
            6 => OpCode::OpDivide,
            7 => OpCode::OpModulo,
            8 => OpCode::OpNil,
            9 => OpCode::OpTrue,
            10 => OpCode::OpFalse,
            11 => OpCode::OpNot,
            12 => OpCode::OpEqual,
            13 => OpCode::OpGreater,
            14 => OpCode::OpLess,
            15 => OpCode::OpPrint,
            16 => OpCode::OpPop,
            17 => OpCode::OpDefineGlobal,
            18 => OpCode::OpGetGlobal,
            _ => unreachable!(),
        }
    }
}

impl Default for VirtualMachine { //just need this for the ui
    fn default() -> Self {
        VirtualMachine::init_machine()
    }
}

// --- Chunk -----------------
#[derive(Debug, Default, Clone)]
pub struct Chunk {
    pub code: Vec<u8>,   // opcode bytes 
    pub lines: Vec<u32>, // line per byte in code
    pub values: Vec<Value>, // constant pool
}

impl Chunk {
    pub fn init_chunk() -> Chunk {
        Chunk {
            code: Vec::new(),
            lines: Vec::new(),
            values: Vec::new(),
        }
    }

    pub fn write_to_chunk(&mut self, byte: u8, linenum: u32) {
        // println!("test print");
        self.code.push(byte);
        self.lines.push(linenum);
    }

    pub fn add_constant(&mut self, num: Value) -> u8 {
      self.values.push(num);
      (self.values.len() - 1) as u8
  }

    // Pretty disassembler you wrote
    pub fn disassemble(&self, name: &str) {
        println!("== {} ==", name);

        let mut offset: usize = 0;
        while offset < self.code.len() {
            let val = self.disassemble_instruction(offset);
            offset += val;
            
           
        }
    }

    pub fn disassemble_instruction(&self, offset: usize) -> usize{
        //println!("{:?}", self.code.get(offset..));
        
            // byte offset
            print!("{:04}  ", offset);

            // line (assumes 1 line per code byte push)
            let line = self.lines[offset];
            print!("{:>3} ", line);

            // decode
            let opcodebyte = self.code[offset];
            let opcode = OpCode::BitToOp(opcodebyte);


            match opcode {
                OpCode::OpConstant => {
                    // one-byte operand: constant index
                    let idxbyte = self.code[offset + 1] as usize;
                    let value = &self.values[idxbyte];
                    println!("OP_CONSTANT         {} {:?}", idxbyte, value);
                    let offset = 2; // opcode + operand
                    offset
                }
                OpCode::OpReturn => {
                    println!("OP_RETURN");
                    let offset = 1;
                    offset
                }
                OpCode::OpNegate => {
                    println!("OP_NEGATE");
                    let offset = 1;
                    offset
                }
                OpCode::OpAdd => {
                    println!("OP_ADD");
                    let offset = 1;
                    offset
                }
                OpCode::OpSubtract => {
                    println!("OP_SUBTRACT");
                    let offset = 1;
                    offset
                }
                OpCode::OpMultiply => {
                    println!("OP_MULTIPLY");
                    let offset = 1;
                    offset
                }
                OpCode::OpDivide => {
                    println!("OP_DIVIDE");
                    let offset = 1;
                    offset
                }
                OpCode::OpModulo => {
                    println!("OP_MODULO");
                    let offset = 1;
                    offset
                }
                OpCode::OpNil =>{
                    println!("OP_NIL");
                    let offset = 1;
                    offset
                }
                OpCode::OpTrue =>{
                    println!("OP_TRUE");
                    let offset = 1;
                    offset
                }
                OpCode::OpFalse =>{
                    println!("OP_FALSE");
                    let offset = 1;
                    offset
                }
                OpCode::OpNot =>{
                    println!("OP_NOT");
                    let offset = 1;
                    offset
                }
                OpCode::OpEqual=>{
                    println!("OP_EQUAL");
                    let offset = 1;
                    offset
                }
                OpCode::OpGreater=>{
                    println!("OP_GREATER");
                    let offset = 1;
                    offset
                }
                OpCode::OpLess=>{
                    println!("OP_LESS");
                    let offset = 1;
                    offset
                }
                OpCode::OpPrint=>{
                    println!("OP_PRINT");
                    let offset = 1;
                    offset
                }
                OpCode::OpPop=>{
                    println!("OP_POP");
                    let offset = 1;
                    offset
                }
                OpCode::OpDefineGlobal=>{
                    println!("OP_OPDEFINEGLOBAL");
                    let offset = 1;
                    offset
                }
                OpCode::OpGetGlobal=>{
                    println!("OP_OPGETGLOBAL");
                    let offset = 1;
                    offset
                }

            }
        }
    }


// --- VM ----------------------------------------------------------------------

pub enum InterpretResult {
    InterpretSuccess,
    InterpretCompileError,
    InterpretRuntimeError,
}

#[derive(Debug)]
pub struct VirtualMachine { //make the actual vm
    pub chunk: Chunk,
    pub ip: usize,     
    pub stack: Vec<Value>,
    pub globals: HashMap<String, Value>,
}

impl VirtualMachine {
    pub fn init_machine() -> VirtualMachine {
        VirtualMachine {
            chunk: Chunk::init_chunk(),
            ip: 0,
            stack: Vec::new(),
            globals: HashMap::new()
            
        }
    }

    pub fn print_value(&self, value: Value) { //printer for vm
        match value {
            Value::ValNil => println!("nil"),
            Value::ValBool(b) => {
                if b {
                    println!("true");
                } else {
                    println!("false");
                }
            }
            Value::ValNumber(n) => println!("{}", n),
            Value::ValString(s) => print!("{}", s),
        }
    }

    fn values_equal(a: Value, b: Value) -> bool {
    match (a, b) {
        (Value::ValBool(x), Value::ValBool(y)) => x == y,
        (Value::ValNumber(x), Value::ValNumber(y)) => x == y,
        (Value::ValNil, Value::ValNil) => true,
        _ => false,
            }
    }
    fn is_falsey(val: &Value) -> bool { //never heard of falsey before, p cool
            match val {
                Value::ValNil => true,
                Value::ValBool(false) => true,
                _ => false,
            }
        }
     fn runtime_error( self: &mut VirtualMachine, message: &str ) {
            println!("{}", message );
            // println!("test print");
            println!("[line {}] in script", self.chunk.lines[self.ip]);
        }

    pub fn interpret(&mut self, chunk: Chunk) -> InterpretResult {
        self.chunk = chunk;
        self.ip = 0;
        self.run()
    }
    pub fn interpret_source(&mut self, source_code: &str) -> InterpretResult {
        // use compiler to produce bytecode
        let mut the_compiler = Compiler::init_compiler();
        if !the_compiler.compile(source_code) {
            println!("Finished Compiling");
            return InterpretResult::InterpretCompileError;
        }
        println!("Starting run");
        self.chunk = the_compiler.get_chunk();
        self.ip = 0;
        self.run()
    }

    pub fn compile(&mut self, source_code: &str) {
        let mut scanner: Scanner = Scanner::init_scanner(source_code);
        let mut line: usize = 0;

        loop {
            let token = scanner.scan_token();

            if token.line != line {
                print!("{:4} ", token.line);
                line = token.line;
            } else {
                print!("   | ");
            }

            println!(
                "{:?} {}, {:?}",
                token.token_type,
                token.length,
                String::from_utf8(token.value.clone())
            );

            if let TokenType::TokenEof = token.token_type {
                break;
            }
        }
    }

    pub fn run(&mut self) -> InterpretResult {

      while self.ip < self.chunk.code.len() {

          let byte = self.chunk.code[self.ip];
          let opcode = OpCode::BitToOp(byte);
          //self.chunk.disassemble_instruction(self.ip);
          println!("{:?}", self.stack);
          
          match opcode {
              OpCode::OpReturn => {
                  self.ip += 1;
                  return InterpretResult::InterpretSuccess;
              }
  
              OpCode::OpConstant => {
                  if self.ip + 1 >= self.chunk.code.len() {
                      return InterpretResult::InterpretRuntimeError;
                  }
                  let idx = self.chunk.code[self.ip + 1] as usize;
                  if idx >= self.chunk.values.len() {
                      return InterpretResult::InterpretRuntimeError;
                  }
                  let val = &self.chunk.values[idx];
                  self.stack.push(val.clone());
                  self.ip += 2;
              }
  
            //   OpCode::OpNegate => {
            //       if let Some(Value::ValNumber(v)) = self.stack.pop() {
            //         //   let neg = (0u8).wrapping_sub(v);
            //         //   self.stack.push(neg);
            //         self.stack.push(Value::ValNumber(v * -1));
            //         self.ip += 1;
            //       } else {
            //           return InterpretResult::InterpretRuntimeError;
            //       }
            //   }
  
              OpCode::OpAdd => {
                  if let (Some(Value::ValNumber(b)), Some(Value::ValNumber(a))) = (self.stack.pop(), self.stack.pop()) {
                      self.stack.push(Value::ValNumber(a.wrapping_add(b)));
                      self.ip += 1;
                  } else {
                      return InterpretResult::InterpretRuntimeError;
                  }
              }
  
              OpCode::OpSubtract => {
                  if let (Some(Value::ValNumber(b)), Some(Value::ValNumber(a))) = (self.stack.pop(), self.stack.pop()) {
                      self.stack.push(Value::ValNumber(a.wrapping_sub(b)));
                      self.ip += 1;
                  } else {
                      return InterpretResult::InterpretRuntimeError;
                  }
              }
  
              OpCode::OpMultiply => {
                  if let (Some(Value::ValNumber(b)), Some(Value::ValNumber(a))) = (self.stack.pop(), self.stack.pop()) {
                      self.stack.push(Value::ValNumber(a.wrapping_mul(b)));
                      self.ip += 1;
                  } else {
                      return InterpretResult::InterpretRuntimeError;
                  }
              }
  
              OpCode::OpDivide => {
                  if let (Some(Value::ValNumber(b)), Some(Value::ValNumber(a))) = (self.stack.pop(), self.stack.pop()) {
                      if b == 0 {
                          return InterpretResult::InterpretRuntimeError;
                      }
                      self.stack.push(Value::ValNumber(a / b));
                      self.ip += 1;
                  } else {
                      return InterpretResult::InterpretRuntimeError;
                  }
              }
  
              OpCode::OpModulo => {
                  if let (Some(Value::ValNumber(b)), Some(Value::ValNumber(a))) = (self.stack.pop(), self.stack.pop()) {
                      if b == 0 {
                          return InterpretResult::InterpretRuntimeError;
                      }
                      self.stack.push(Value::ValNumber(a % b));
                      self.ip += 1;
                  } else {
                      return InterpretResult::InterpretRuntimeError;
                  }
              }

              OpCode::OpNegate =>{
                match self.stack.pop(){
                    Some(Value::ValNumber(n)) => self.stack.push(Value::ValNumber(-n)),
                    Some(_) => {
                        self.runtime_error("Operand must be a number");
                        self.ip += 1;
                        return InterpretResult::InterpretRuntimeError
                    }
                    None => {
                        self.runtime_error("Operand must be a number");
                        return InterpretResult::InterpretRuntimeError
                    }
                }
              }

              OpCode::OpNil=>{
                match self.stack.pop(){
                    Some(v)=>{
                        self.stack.push(Value::ValNil);
                        self.ip += 1;
                    }
                    None =>{
                        return InterpretResult::InterpretRuntimeError;
                    }
                }
              }

              OpCode::OpFalse=>{
                match self.stack.pop(){
                    Some(v)=>{
                        self.stack.push(Value::ValBool(false));
                        self.ip += 1;
                        // self.ip += 1;
                    }
                    None =>{
                        return InterpretResult::InterpretRuntimeError;
                    }
                }
              }
              OpCode::OpTrue=>{
                match self.stack.pop(){
                    Some(v)=>{
                        self.stack.push(Value::ValBool(true));
                        self.ip += 1;
                    }
                    None =>{
                        return InterpretResult::InterpretRuntimeError;
                    }
                }
              }
              OpCode::OpNot => {
                  match self.stack.pop() {
                      Some(v) => {
                          let result = !VirtualMachine::is_falsey(&v);
                          self.stack.push(Value::ValBool(result));
                          self.ip += 1;
                      }
                      None => {
                          return InterpretResult::InterpretRuntimeError;
                      }
                  }
              }
             OpCode::OpEqual =>{
                if let (Some(Value::ValNumber(b)), Some(Value::ValNumber(a))) = (self.stack.pop(), self.stack.pop()) {
                      if b == a {
                          self.stack.push(Value::ValBool(true));
                          self.ip += 1;
                      }
                      if b != a {
                        self.stack.push(Value::ValBool(false));
                        self.ip += 1;
                      }
                      
                  } else {
                      return InterpretResult::InterpretRuntimeError;
                  }
             } 
             OpCode::OpGreater =>{
                     if let (Some(Value::ValNumber(b)), Some(Value::ValNumber(a))) =
                        (self.stack.pop(), self.stack.pop())
                    {
                        if a > b {
                            self.stack.push(Value::ValBool(true));
                            self.ip += 1;
                        } else {
                            self.stack.push(Value::ValBool(false));
                            self.ip += 1;
                        }
                    } else {
                        return InterpretResult::InterpretRuntimeError;
                    }
             }
             OpCode::OpLess=>{
                    if let (Some(Value::ValNumber(b)), Some(Value::ValNumber(a))) =
                        (self.stack.pop(), self.stack.pop())
                    {
                        if a < b {
                            self.stack.push(Value::ValBool(true));
                            self.ip += 1;
                        } else {
                            self.stack.push(Value::ValBool(false));
                            self.ip += 1;
                        }
                    } else {
                        return InterpretResult::InterpretRuntimeError;
                    }
             }
             OpCode::OpPrint => {
                  if let Some(value) = self.stack.pop() {
                      self.print_value(value);
                      self.ip += 1;
                  } else {
                      self.runtime_error("print underflow :( ");
                      return InterpretResult::InterpretRuntimeError;
                  }
              }
            OpCode::OpPop =>{
                    // Just discard the top of the stack
                    self.stack.pop();
                    self.ip += 1;
            }
            OpCode::OpDefineGlobal =>{
            
                let name_index = self.chunk.code[self.ip + 1] as usize;
                
                let name_val = self.chunk.values[name_index].clone();

                let var_name = match name_val {
                    Value::ValString(s) => s,
                    _ => {
                        self.runtime_error("Global variable name must be a string.");
                        return InterpretResult::InterpretRuntimeError;
                    }
                };
                
                let value = match self.stack.pop() {
                    Some(v) => v,
                    None => {
                        self.runtime_error("Stack underflow while defining global.");
                        return InterpretResult::InterpretRuntimeError;
                    }
                };

                self.globals.insert(var_name, value);
                self.ip += 2;  
            }
            OpCode::OpGetGlobal =>{
                     
                let name_index = self.chunk.code[self.ip + 1] as usize;

                let name_val = self.chunk.values[name_index].clone();

                let var_name = match name_val {
                    Value::ValString(s) => s,
                    _ => {
                        self.runtime_error("Global variable name must be a string.");
                        return InterpretResult::InterpretRuntimeError;
                    }
                };

                
                let value = match self.globals.get(&var_name) {
                    Some(v) => v.clone(),
                    None => {
                        self.runtime_error(&format!("Undefined global '{}'.", var_name));
                        return InterpretResult::InterpretRuntimeError;
                    }
                };

                
                self.stack.push(value);

               
                self.ip += 2;
                }
        }
          
          
      }
  
      InterpretResult::InterpretSuccess
    }
}


 


#[cfg(test)]
mod tests {
    use super::*;

    fn push_const(chunk: &mut Chunk, line: u32, v: Value) {
        let idx = chunk.add_constant(v);
        chunk.write_to_chunk(OpCode::OpToBit(OpCode::OpConstant), line);
        chunk.write_to_chunk(idx, line);
    }

    fn push_op(chunk: &mut Chunk, line: u32, op: OpCode) {
        chunk.write_to_chunk(OpCode::OpToBit(op), line);
    }

    fn run(chunk: Chunk) -> (InterpretResult, Vec<Value>) {
        let mut vm = VirtualMachine::init_machine();
        let res = vm.interpret(chunk);
        (res, vm.stack)
    }

    #[test]
    fn opcode_roundtrip() {
        let ops = [
            OpCode::OpReturn,
            OpCode::OpConstant,
            OpCode::OpNegate,
            OpCode::OpAdd,
            OpCode::OpSubtract,
            OpCode::OpMultiply,
            OpCode::OpDivide,
            OpCode::OpModulo,
        ];
        for op in ops {
            let b = OpCode::OpToBit(op);
            let round = OpCode::BitToOp(b);
            assert_eq!(op, round, "Roundtrip failed for {:?}", op);
        }
    }

    #[test]
    fn line_tracking_matches_code_bytes() {
        let mut c = Chunk::init_chunk();
        push_const(&mut c, 100, Value::ValNumber(1));
        push_const(&mut c, 101, Value::ValNumber(2));
        push_op(&mut c, 102, OpCode::OpAdd);
        push_op(&mut c, 103, OpCode::OpReturn);

        assert_eq!(c.code.len(), c.lines.len(), "code/line length mismatch");
        assert_eq!(
            c.values,
            vec![Value::ValNumber(1), Value::ValNumber(2)]
        );
        assert_eq!(c.lines[0], 100);
        assert_eq!(c.lines[2], 101);
        assert_eq!(c.lines[4], 102);
        assert_eq!(c.lines[5], 103);
    }

    #[test]
    fn disassemble_instruction_offsets() {
        let mut c = Chunk::init_chunk();
        push_const(&mut c, 10, Value::ValNumber(42));    // 2 bytes
        push_op(&mut c, 11, OpCode::OpNegate); // 1 byte
        push_op(&mut c, 12, OpCode::OpReturn); // 1 byte

        let mut off = 0;
        off += c.disassemble_instruction(off);
        assert_eq!(off, 2);
        off += c.disassemble_instruction(off);
        assert_eq!(off, 3);
        off += c.disassemble_instruction(off);
        assert_eq!(off, 4);
        assert_eq!(off, c.code.len());
    }

    #[test]
    fn constant_and_return_stack_top() {
        let mut c = Chunk::init_chunk();
        push_const(&mut c, 1, Value::ValNumber(123));
        push_op(&mut c, 2, OpCode::OpReturn);

        let (res, stack) = run(c);
        assert!(matches!(res, InterpretResult::InterpretSuccess));
        assert_eq!(stack, vec![Value::ValNumber(123)]);
    }

    #[test]
    fn add_sub_mul_div_mod_chain() {
        let mut c = Chunk::init_chunk();

        push_const(&mut c, 123, Value::ValNumber(42));
        push_const(&mut c, 124, Value::ValNumber(18));
        push_op(&mut c, 125, OpCode::OpAdd);

        push_const(&mut c, 126, Value::ValNumber(32));
        push_op(&mut c, 127, OpCode::OpDivide);

        push_const(&mut c, 128, Value::ValNumber(37));
        push_op(&mut c, 129, OpCode::OpMultiply);

        push_const(&mut c, 130, Value::ValNumber(85));
        push_op(&mut c, 131, OpCode::OpModulo);

        push_const(&mut c, 132, Value::ValNumber(12));
        push_op(&mut c, 133, OpCode::OpNegate);

        push_op(&mut c, 134, OpCode::OpReturn);

        let (res, stack) = run(c);
        assert!(matches!(res, InterpretResult::InterpretSuccess));
        // (((42 + 18) / 32) * 37) % 85 = 37; 12 -> negate => -12
        assert_eq!(
            stack,
            vec![
                Value::ValNumber(37),
                Value::ValNumber(-12),
            ]
        );
    }

    #[test]
    fn negate_positive_and_negative() {
        let mut c = Chunk::init_chunk();
        push_const(&mut c, 10, Value::ValNumber(7));
        push_op(&mut c, 11, OpCode::OpNegate); // -> -7
        push_const(&mut c, 12, Value::ValNumber(-3));
        push_op(&mut c, 13, OpCode::OpNegate); // -> +3
        push_op(&mut c, 14, OpCode::OpReturn);

        let (res, stack) = run(c);
        assert!(matches!(res, InterpretResult::InterpretSuccess));
        assert_eq!(
            stack,
            vec![
                Value::ValNumber(-7),
                Value::ValNumber(3),
            ]
        );
    }

    #[test]
    fn wrapping_add_sub_mul() {
        let mut c = Chunk::init_chunk();
        push_const(&mut c, 1, Value::ValNumber(i16::MAX)); // 32767
        push_const(&mut c, 2, Value::ValNumber(1));
        push_op(&mut c, 3, OpCode::OpAdd); // wraps to -32768

        push_const(&mut c, 4, Value::ValNumber(i16::MIN)); // -32768
        push_const(&mut c, 5, Value::ValNumber(1));
        push_op(&mut c, 6, OpCode::OpSubtract); // (-32768) - 1 => wraps to 32767

        push_const(&mut c, 7, Value::ValNumber(2000));
        push_const(&mut c, 8, Value::ValNumber(20));
        push_op(&mut c, 9, OpCode::OpMultiply); 

        push_op(&mut c, 10, OpCode::OpReturn);

        let (res, stack) = run(c);
        assert!(matches!(res, InterpretResult::InterpretSuccess));

        let a = i16::MAX.wrapping_add(1);
        let b = i16::MIN.wrapping_sub(1);
        let cval = 2000i16.wrapping_mul(20);

        assert_eq!(
            stack,
            vec![
                Value::ValNumber(a),
                Value::ValNumber(b),
                Value::ValNumber(cval),
            ]
        );
    }

    #[test]
    fn error_missing_constant_operand() {
        let mut c = Chunk::init_chunk();
        push_op(&mut c, 1, OpCode::OpConstant);
        // no operand byte
        let (res, _stack) = run(c);
        assert!(matches!(res, InterpretResult::InterpretRuntimeError));
    }

    #[test]
    fn error_bad_constant_index() {
        // OpConstant with index that is out of bounds
        let mut c = Chunk::init_chunk();
        c.write_to_chunk(OpCode::OpToBit(OpCode::OpConstant), 1);
        c.write_to_chunk(99, 1); 
        let (res, _stack) = run(c);
        assert!(matches!(res, InterpretResult::InterpretRuntimeError));
    }

    #[test]
    fn error_stack_underflow_binary_ops() {
        //try each binary op with insufficient stack
        for op in [
            OpCode::OpAdd,
            OpCode::OpSubtract,
            OpCode::OpMultiply,
            OpCode::OpDivide,
            OpCode::OpModulo,
        ] {
            let mut c = Chunk::init_chunk();
            //push only one constant, then a binary op
            push_const(&mut c, 10, Value::ValNumber(1));
            push_op(&mut c, 11, op);
            let (res, _stack) = run(c);
            assert!(
                matches!(res, InterpretResult::InterpretRuntimeError),
                "Expected runtime error for {:?} with one operand",
                op
            );
        }
    }

    #[test]
    fn error_divide_by_zero() {
        let mut c = Chunk::init_chunk();
        push_const(&mut c, 1, Value::ValNumber(10));
        push_const(&mut c, 2, Value::ValNumber(0));
        push_op(&mut c, 3, OpCode::OpDivide);
        let (res, _stack) = run(c);
        assert!(matches!(res, InterpretResult::InterpretRuntimeError));
    }

    #[test]
    fn error_mod_by_zero() {
        let mut c = Chunk::init_chunk();
        push_const(&mut c, 1, Value::ValNumber(10));
        push_const(&mut c, 2, Value::ValNumber(0));
        push_op(&mut c, 3, OpCode::OpModulo);
        let (res, _stack) = run(c);
        assert!(matches!(res, InterpretResult::InterpretRuntimeError));
    }

    #[test]
    fn return_terminates_execution() {
        let mut c = Chunk::init_chunk();
        push_const(&mut c, 1, Value::ValNumber(5));
        push_op(&mut c, 2, OpCode::OpReturn);
        // garbage after return (should never execute)
        push_const(&mut c, 999, Value::ValNumber(12345));
        push_op(&mut c, 999, OpCode::OpAdd);

        let (res, stack) = run(c);
        assert!(matches!(res, InterpretResult::InterpretSuccess));
        assert_eq!(
            stack,
            vec![Value::ValNumber(5)],
            "VM should stop executing after OpReturn"
        );
    }

    #[test]
    fn left_to_right() {
        // ((8 - 3) * 2) + (20 / 5) % 6 = (5 * 2) + (4) % 6 = 10 + 4 = 14
        let mut c = Chunk::init_chunk();
        push_const(&mut c, 1, Value::ValNumber(8));
        push_const(&mut c, 2, Value::ValNumber(3));
        push_op(&mut c, 3, OpCode::OpSubtract);  // 5

        push_const(&mut c, 4, Value::ValNumber(2));
        push_op(&mut c, 5, OpCode::OpMultiply); 

        push_const(&mut c, 6, Value::ValNumber(20));
        push_const(&mut c, 7, Value::ValNumber(5));
        push_op(&mut c, 8, OpCode::OpDivide);    // 4

        push_const(&mut c, 9, Value::ValNumber(6));
        push_op(&mut c, 10, OpCode::OpModulo);   

        push_op(&mut c, 11, OpCode::OpAdd);      // idk what else
        push_op(&mut c, 12, OpCode::OpReturn);

        let (res, stack) = run(c);
        assert!(matches!(res, InterpretResult::InterpretSuccess));
        assert_eq!(stack, vec![Value::ValNumber(14)]);
    }

    fn collect_tokens(src: &str) -> Vec<TokenType> {
        let mut s = Scanner::init_scanner(src);
        let mut out = Vec::new();
        loop {
            let t = s.scan_token();
            out.push(t.token_type);
            if matches!(t.token_type, TokenType::TokenEof) { break; }
        }
        out
    }

    #[test]
    fn scan_single_char_tokens() {
        let src = "(){};,.-+*/";
        let got = collect_tokens(src);
        use TokenType::*;
        let expect = vec![
            TokenLeftParen, TokenRightParen,
            TokenLeftBrace, TokenRightBrace,
            TokenSemicolon,
            TokenComma,
            TokenDot,
            TokenMinus, TokenPlus,
            TokenStar,
            TokenSlash,
            TokenEof,
        ];
        assert_eq!(got, expect);
    }

    #[test]
    fn scan_2x_comparisons() {
        let src = "! != = == < <= > >=";
        let got = collect_tokens(src);
        use TokenType::*;
        let expect = vec![
            TokenNot, TokenNotEqual, TokenEqual, TokenEqualEqual,
            TokenLess, TokenLessEqual, TokenGreater, TokenGreaterEqual,
            TokenEof,
        ];
        assert_eq!(got, expect);
    }

    #[test]
    fn scan_numbers_and_identifiers() {
        let src = "var x = 12.34\ny_2 = 7\n";
        let mut s = Scanner::init_scanner(src);

        let mut next = || s.scan_token().token_type;

        use TokenType::*;
        assert_eq!(next(), TokenVar);
        assert_eq!(next(), TokenIdentifier); // x
        assert_eq!(next(), TokenEqual);
        assert_eq!(next(), TokenNumber);     // 12.34
        assert_eq!(next(), TokenIdentifier); // y_2 
        assert_eq!(next(), TokenEqual);
        assert_eq!(next(), TokenNumber);     // 7
        assert_eq!(next(), TokenEof);
    }

    #[test]
    fn scan_comments() {
        let src = r#"
            // this is a comment
            print "67";
            // another comment
        "#;

        let got = collect_tokens(src);
        use TokenType::*;
        let expect = vec![
            TokenPrint, TokenString, TokenSemicolon,
            TokenEof,
        ];
        assert_eq!(got, expect);
    }

    #[test]
    fn unterminated_string_errors() {
        let src = "print \"oops";
        let mut s = Scanner::init_scanner(src);

        let _ = s.scan_token(); // print
        let tok = s.scan_token(); // should be error
        assert!(matches!(tok.token_type, TokenType::TokenError));
        let msg = String::from_utf8(tok.value).unwrap();
        assert!(msg.contains("Unterminated"), "got error: {}", msg);
    }

    #[test]
    fn keyword_recognition() {
        let src = "and class else false for fun if nil or print return super this true var while";
        let got = collect_tokens(src);
        use TokenType::*;
        let expect = vec![
            TokenAnd, TokenClass, TokenElse, TokenFalse, TokenFor, TokenFun,
            TokenIf, TokenNil, TokenOr, TokenPrint, TokenReturn, TokenSuper,
            TokenThis, TokenTrue, TokenVar, TokenWhile, TokenEof,
        ];
        assert_eq!(got, expect);
    }


}
