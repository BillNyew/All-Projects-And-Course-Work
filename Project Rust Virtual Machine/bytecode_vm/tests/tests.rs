#[cfg(test)]
mod tests{
    //TEST 1 - SINGLE NUMBER

    use bytecode_vm::{VirtualMachine, Chunk, OpCode, Value, InterpretResult};

    #[test]
    fn single_number_program_result_one() {
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value: Value = 67;
        let const_idx = chunk.add_constant(constant_value);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx, 1); // operand
        chunk.write_to_chunk(OpCode::OpReturn as u8, 1); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![constant_value]); //assert that we have the value
    }
    #[test]
    fn single_number_program_result_two(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value: Value = -67;
        let const_idx = chunk.add_constant(constant_value);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx, 1); // operand
        chunk.write_to_chunk(OpCode::OpReturn as u8, 1); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![constant_value]); //assert that we have the value
    }

     #[test]
    fn single_number_program_result_three(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value: Value = 0;
        let const_idx = chunk.add_constant(constant_value);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx, 1); // operand
        chunk.write_to_chunk(OpCode::OpReturn as u8, 1); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![constant_value]); //assert that we have the value
    }

     #[test]
    fn single_number_program_result_four(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value: Value = -0;
        let const_idx = chunk.add_constant(constant_value);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx, 1); // operand
        chunk.write_to_chunk(OpCode::OpReturn as u8, 1); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![constant_value]); //assert that we have the value
    }
     #[test]
    fn single_number_program_result_five(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value: Value = 32767;
        let const_idx = chunk.add_constant(constant_value);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx, 1); // operand
        chunk.write_to_chunk(OpCode::OpReturn as u8, 1); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![constant_value]); //assert that we have the value
    }
     #[test]
    fn single_number_program_result_six(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value: Value = -32767;
        let const_idx = chunk.add_constant(constant_value);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx, 1); // operand
        chunk.write_to_chunk(OpCode::OpReturn as u8, 1); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![constant_value]); //assert that we have the value
    }
     #[test]
    fn single_number_program_result_seven(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value: Value = 9856;
        let const_idx = chunk.add_constant(constant_value);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx, 1); // operand
        chunk.write_to_chunk(OpCode::OpReturn as u8, 1); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![constant_value]); //assert that we have the value
    }
     #[test]
    fn single_number_program_result_eight(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value: Value = 37;
        let const_idx = chunk.add_constant(constant_value);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx, 1); // operand
        chunk.write_to_chunk(OpCode::OpReturn as u8, 1); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![constant_value]); //assert that we have the value
    }
     #[test]
    fn single_number_program_result_nine(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value: Value = 7886;
        let const_idx = chunk.add_constant(constant_value);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx, 2); // operand
        chunk.write_to_chunk(OpCode::OpReturn as u8, 3); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![constant_value]); //assert that we have the value
    }


    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////   
    
    //TEST 2 - ADDITION

         #[test]
    fn addition_program_result_1(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value = 1;
        let constant_value_2: Value = 2;
        let answer = constant_value_1 + constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operand
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpAdd as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpReturn as u8, 6); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }

             #[test]
    fn addition_program_result_2(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value = -6;
        let constant_value_2: Value = 7;
        let answer = constant_value_1 + constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operand
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpAdd as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpReturn as u8, 6); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }

             #[test]
    fn addition_program_result_3(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value = 6;
        let constant_value_2: Value = -7;
        let answer = constant_value_1 + constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operand
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpAdd as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpReturn as u8, 6); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }

             #[test]
    fn addition_program_result_4(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value = 300;
        let constant_value_2: Value = 0;
        let answer = constant_value_1 + constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operand
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpAdd as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpReturn as u8, 6); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }

             #[test]
    fn addition_program_result_5(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value = -23;
        let constant_value_2: Value = -2;
        let answer = constant_value_1 + constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operand
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpAdd as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpReturn as u8, 6); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }

             #[test]
    fn addition_program_result_6(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value = -2;
        let constant_value_2: Value = 2;
        let answer = constant_value_1 + constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operand
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpAdd as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpReturn as u8, 6); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }

             #[test]
    fn addition_program_result_7(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value = 32765;
        let constant_value_2: Value = 1;
        let answer = constant_value_1 + constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operand
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpAdd as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpReturn as u8, 6); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }

             #[test]
    fn addition_program_result_8(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value = -32766;
        let constant_value_2: Value = -1;
        let answer = constant_value_1 + constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operand
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpAdd as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpReturn as u8, 6); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }

             #[test]
    fn addition_program_result_9(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value = 0;
        let constant_value_2: Value = 0;
        let answer = constant_value_1 + constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operanda
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpAdd as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpReturn as u8, 6); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }

    
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////   
    
    //TEST 3 - SUBTRACTION
    #[test]
    fn multiplication_program_result_1(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value = 1;
        let constant_value_2: Value = 2;
        let answer = constant_value_1 * constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operanda
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpMultiply as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpReturn as u8, 6); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }

    #[test]
    fn multiplication_program_result_2(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value = 1;
        let constant_value_2: Value = 0;
        let answer = constant_value_1 * constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operanda
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpMultiply as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpReturn as u8, 6); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }
    #[test]
    fn multiplication_program_result_3(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value = -1;
        let constant_value_2: Value = 0;
        let answer = constant_value_1 * constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operanda
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpMultiply as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpReturn as u8, 6); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }
    #[test]
    fn multiplication_program_result_4(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value = 0;
        let constant_value_2: Value = 0;
        let answer = constant_value_1 * constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operanda
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpMultiply as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpReturn as u8, 6); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }
    #[test]
    fn multiplication_program_result_5(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value = -20;
        let constant_value_2: Value = 2;
        let answer = constant_value_1 * constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operanda
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpMultiply as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpReturn as u8, 6); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }
    #[test]
    fn multiplication_program_result_6(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value = 20;
        let constant_value_2: Value = -2;
        let answer = constant_value_1 * constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operanda
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpMultiply as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpReturn as u8, 6); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }
    #[test]
    fn multiplication_program_result_7(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value = -6;
        let constant_value_2: Value = -7;
        let answer = constant_value_1 * constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operanda
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpMultiply as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpReturn as u8, 6); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }
    #[test]
    fn multiplication_program_result_8(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value = 1;
        let constant_value_2: Value = 1;
        let answer = constant_value_1 * constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operanda
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpMultiply as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpReturn as u8, 6); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }
    #[test]
    fn multiplication_program_result_9(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value = 40;
        let constant_value_2: Value = 2;
        let answer = constant_value_1 * constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operanda
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpMultiply as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpReturn as u8, 6); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }
    
        
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////   
    
    //TEST 4 - SUBTRACTION


        #[test]
    fn subtraction_program_result_1(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value = 40;
        let constant_value_2: Value = 15;
        let answer = constant_value_1 - constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operanda
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpSubtract as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpReturn as u8, 6); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }

        #[test]
    fn subtraction_program_result_2(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value = -40;
        let constant_value_2: Value = 15;
        let answer = constant_value_1 - constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operanda
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpSubtract as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpReturn as u8, 6); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }

        #[test]
    fn subtraction_program_result_3(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value = -40;
        let constant_value_2: Value = -15;
        let answer = constant_value_1 - constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operanda
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpSubtract as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpReturn as u8, 6); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }

        #[test]
    fn subtraction_program_result_4(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value = 40;
        let constant_value_2: Value = -15;
        let answer = constant_value_1 - constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operanda
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpSubtract as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpReturn as u8, 6); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }

        #[test]
    fn subtraction_program_result_5(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value = 0;
        let constant_value_2: Value = 50;
        let answer = constant_value_1 - constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operanda
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpSubtract as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpReturn as u8, 6); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }

        #[test]
    fn subtraction_program_result_6(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value = 0;
        let constant_value_2: Value = -50;
        let answer = constant_value_1 - constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operanda
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpSubtract as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpReturn as u8, 6); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }

        #[test]
    fn subtraction_program_result_7(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value = 0;
        let constant_value_2: Value = 0;
        let answer = constant_value_1 - constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operanda
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpSubtract as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpReturn as u8, 6); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }

        #[test]
    fn subtraction_program_result_8(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value = 1;
        let constant_value_2: Value = 1;
        let answer = constant_value_1 - constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operanda
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpSubtract as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpReturn as u8, 6); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }

        #[test]
    fn subtraction_program_result_9(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value = 4566;
        let constant_value_2: Value = 320;
        let answer = constant_value_1 - constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operanda
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpSubtract as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpReturn as u8, 6); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////   
    
    //TEST 5 - DIVISION


        #[test]
    fn division_program_result_1(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value = 0;
        let constant_value_2: Value = 1;
        let answer = constant_value_1 / constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operanda
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpDivide as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpReturn as u8, 6); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }

    #[test]
    fn division_program_result_2(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value = 1;
        let constant_value_2: Value = 1;
        let answer = constant_value_1 / constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operanda
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpDivide as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpReturn as u8, 6); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }
    #[test]
    fn division_program_result_3(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value = 30;
        let constant_value_2: Value = 2;
        let answer = constant_value_1 / constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operanda
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpDivide as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpReturn as u8, 6); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }
    #[test]
    fn division_program_result_4(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value = 30;
        let constant_value_2: Value = -2;
        let answer = constant_value_1 / constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operanda
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpDivide as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpReturn as u8, 6); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }
    #[test]
    fn division_program_result_5(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value = 13;
        let constant_value_2: Value = 2;
        let answer = constant_value_1 / constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operanda
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpDivide as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpReturn as u8, 6); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }
    #[test]
    fn division_program_result_6(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value = 5;
        let constant_value_2: Value = 30;
        let answer = constant_value_1 / constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operanda
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpDivide as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpReturn as u8, 6); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }
    #[test]
    fn division_program_result_7(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value = -5;
        let constant_value_2: Value = 30;
        let answer = constant_value_1 / constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operanda
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpDivide as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpReturn as u8, 6); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }
    #[test]
    fn division_program_result_8(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value = -13;
        let constant_value_2: Value = 2;
        let answer = constant_value_1 / constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operanda
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpDivide as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpReturn as u8, 6); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }
    #[test]
    fn division_program_result_9(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value = 13;
        let constant_value_2: Value = -2;
        let answer = constant_value_1 / constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operanda
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpDivide as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpReturn as u8, 6); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////   
    
    //TEST 6 - MULTIPLE OPERATORS


        #[test]
    fn multiple_op_program_result_1(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value = 4;
        let constant_value_2: Value = 8;
        let answer = (constant_value_1 + constant_value_2) * constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operand
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpAdd as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpConstant as u8, 6); // opcode
        chunk.write_to_chunk(const_idx_2,7); // operand
        chunk.write_to_chunk(OpCode::OpMultiply as u8, 8); // opcode

        chunk.write_to_chunk(OpCode::OpReturn as u8, 9); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }

        #[test]
    fn multiple_op_program_result_2(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value = 0;
        let constant_value_2: Value = 0;
        let answer = (constant_value_1 + constant_value_2) * constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operand
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpAdd as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpConstant as u8, 6); // opcode
        chunk.write_to_chunk(const_idx_2,7); // operand
        chunk.write_to_chunk(OpCode::OpMultiply as u8, 8); // opcode

        chunk.write_to_chunk(OpCode::OpReturn as u8, 9); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }

        #[test]
    fn multiple_op_program_result_3(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value = 1;
        let constant_value_2: Value = 1;
        let answer = (constant_value_1 + constant_value_2) * constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operand
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpAdd as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpConstant as u8, 6); // opcode
        chunk.write_to_chunk(const_idx_2,7); // operand
        chunk.write_to_chunk(OpCode::OpMultiply as u8, 8); // opcode

        chunk.write_to_chunk(OpCode::OpReturn as u8, 9); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }

        #[test]
    fn multiple_op_program_result_4(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value = -4;
        let constant_value_2: Value = -8;
        let answer = (constant_value_1 + constant_value_2) * constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operand
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpAdd as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpConstant as u8, 6); // opcode
        chunk.write_to_chunk(const_idx_2,7); // operand
        chunk.write_to_chunk(OpCode::OpMultiply as u8, 8); // opcode

        chunk.write_to_chunk(OpCode::OpReturn as u8, 9); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }

        #[test]
    fn multiple_op_program_result_5(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value = -6;
        let constant_value_2: Value = 7;
        let answer = (constant_value_1 + constant_value_2) * constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operand
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpAdd as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpConstant as u8, 6); // opcode
        chunk.write_to_chunk(const_idx_2,7); // operand
        chunk.write_to_chunk(OpCode::OpMultiply as u8, 8); // opcode

        chunk.write_to_chunk(OpCode::OpReturn as u8, 9); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }

        #[test]
    fn multiple_op_program_result_6(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value = 0;
        let constant_value_2: Value = -9;
        let answer = (constant_value_1 + constant_value_2) * constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operand
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpAdd as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpConstant as u8, 6); // opcode
        chunk.write_to_chunk(const_idx_2,7); // operand
        chunk.write_to_chunk(OpCode::OpMultiply as u8, 8); // opcode

        chunk.write_to_chunk(OpCode::OpReturn as u8, 9); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }

        #[test]
    fn multiple_op_program_result_7(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value =-34;
        let constant_value_2: Value = 83;
        let answer = (constant_value_1 + constant_value_2) * constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operand
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpAdd as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpConstant as u8, 6); // opcode
        chunk.write_to_chunk(const_idx_2,7); // operand
        chunk.write_to_chunk(OpCode::OpMultiply as u8, 8); // opcode

        chunk.write_to_chunk(OpCode::OpReturn as u8, 9); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }

        #[test]
    fn multiple_op_program_result_8(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value = 0;
        let constant_value_2: Value = -0;
        let answer = (constant_value_1 + constant_value_2) * constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operand
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpAdd as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpConstant as u8, 6); // opcode
        chunk.write_to_chunk(const_idx_2,7); // operand
        chunk.write_to_chunk(OpCode::OpMultiply as u8, 8); // opcode

        chunk.write_to_chunk(OpCode::OpReturn as u8, 9); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }

        #[test]
    fn multiple_op_program_result_9(){
        // create chunk
        let mut chunk = Chunk::init_chunk();
        let constant_value_1: Value = 1;
        let constant_value_2: Value = 111;
        let answer = (constant_value_1 + constant_value_2) * constant_value_2;
        let const_idx_1 = chunk.add_constant(constant_value_1);
        let const_idx_2 = chunk.add_constant(constant_value_2);
        chunk.write_to_chunk(OpCode::OpConstant as u8, 1); // opcode
        chunk.write_to_chunk(const_idx_1, 2); // operand
        chunk.write_to_chunk(OpCode::OpConstant as u8, 3); // opcode
        chunk.write_to_chunk(const_idx_2,4); // operand
        chunk.write_to_chunk(OpCode::OpAdd as u8, 5); // opcode
        chunk.write_to_chunk(OpCode::OpConstant as u8, 6); // opcode
        chunk.write_to_chunk(const_idx_2,7); // operand
        chunk.write_to_chunk(OpCode::OpMultiply as u8, 8); // opcode

        chunk.write_to_chunk(OpCode::OpReturn as u8, 9); // return

        // run chunk in vm
        let mut vm = VirtualMachine::init_machine();
        let _ = vm.interpret(chunk);
        assert_eq!(vm.stack, vec![answer]); //assert that we have the value
    }



}
