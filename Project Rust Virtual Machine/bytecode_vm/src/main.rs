use std::env;
use std::io;
use std::io::Write;
use std::fs;
use bytecode_vm::VirtualMachine; // only what's needed

fn main() {
    // initialize vm
    let mut vm: VirtualMachine = VirtualMachine::init_machine();

    
    let args: Vec<String> = env::args().collect();
    dbg!(&args);

    if args.len() == 1 {
        read_eval_print_loop(&mut vm);
    } else if args.len() == 2 {
        run_file(&mut vm, &args[1]);
    } else {
        println!("Usage: ");
        println!("    cargo run");
        println!("        to use the lox read-eval-print-loop");
        println!("    cargo run -- lox_program_file_name");
        println!("        to execute a lox program file");
    }
}

fn read_eval_print_loop(vm: &mut VirtualMachine) {
    loop {
        //print here
        print!("> ");
        io::stdout().flush().expect("flush failed");

        // ask user for line
        let mut lox_code = String::new();
        io::stdin().read_line(&mut lox_code).expect("Failed to read line");


        vm.interpret_source(&lox_code);
    }
}

fn run_file(vm: &mut VirtualMachine, infile: &str) {
    let lox_code = fs::read_to_string(infile).expect("Unable to read the file");
    vm.compile(&lox_code);
}
