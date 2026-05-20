use crossterm::{
    ExecutableCommand, cursor::{MoveTo}, event::{self, Event, KeyCode}, terminal::{Clear, EnterAlternateScreen, LeaveAlternateScreen, disable_raw_mode, enable_raw_mode, is_raw_mode_enabled}
};

use std::{mem::type_info::Str, process::Command, thread::sleep};
use std::io::{stdout, Write};

fn print_raw(text: &str) -> Result<(), Box<dyn std::error::Error>>{
    if is_raw_mode_enabled()?{
        disable_raw_mode()?;
        println!("\r\n{}",text);
        enable_raw_mode()?;
    }
    else {
        println!("Salida: \r\n{}",text);
    }
    Ok(())

}

fn display_options(options: &[&str], selected: usize) -> Result<(), Box<dyn std::error::Error>>{
    if !is_raw_mode_enabled()?{
        enable_raw_mode()?;
    }

    print!("Iwdtui: \r\n");
    for (idx, option) in options.iter().enumerate(){
        if idx == selected{
            print!("> {}\x1b[K\r\n", option);
        }
        else {
            print!("  {}\x1b[K\r\n", option);
        }
    }
    stdout().flush()?;


    Ok(())
}

fn main() -> Result<(), Box<dyn std::error::Error>> {
    if cfg!(target_os = "windows"){
        return Err(Box::from("Error: iwdtui no es compatible con windows"));
    }

    enable_raw_mode()?;
    stdout().execute(EnterAlternateScreen)?;

    let options = ["scan", "get-networks", "connect"];
    let interface = ;
    let mut output: String = String::new();

    let mut selected: usize = 0;

    loop {
        stdout().execute(MoveTo(0, 0))?;
        stdout().execute(Clear(crossterm::terminal::ClearType::All))?;

        display_options(&options, selected)?;
        print_raw(&output)?;


        if let Event::Key(key_event) = event::read()? {
            match key_event.code {
                KeyCode::Char('q') => break,

                KeyCode::Down => {
                    if selected < options.len() - 1 {
                        selected += 1;
                    }
                },
                KeyCode::Up => {
                    if selected > 0 {
                        selected -= 1;
                    }
                },
                KeyCode::Enter => {
                    stdout().execute(MoveTo(0, (options.len() + 1) as u16))?;
                    match selected {
                        0 => {
                            scan_networks(interface)?;
                            sleep(std::time::Duration::from_millis(5));
                        },
                        1 => {
                            output = get_networks(interface)?;
                            print_raw(&output)?;
                            sleep(std::time::Duration::from_millis(5000));
                        }
                        2 => {

                        }
                        _ => {

                        }
                        
                    }
                }

                _ => {}
            }

        }
    }

    disable_raw_mode()?;
    stdout().execute(LeaveAlternateScreen)?;
    Ok(())
}

fn get_interfaces() -> Result<Vec<String>, Box<dyn std::error::Error>> {
    let mut get_interfaces_cmd = Command::new("iwctl");
    get_interfaces_cmd.args(["station", "list"]);
    let result =  get_interfaces_cmd.output()?;
    let text  = String::from_utf8_lossy(&result.stdout);
    let interfaces = text
        .lines()
        .skip(4);
    for line in interfaces {
        let line_trimmed = line.trim();
    }
    Ok(interfaces)
}

fn scan_networks(interface: &str) -> Result<(), Box<dyn std::error::Error>>{
    let mut scan_cmd = Command::new("iwctl");
    scan_cmd.args(["station", &interface, "scan"]);
    
    scan_cmd.output()?;


    Ok(())
}

fn get_networks(interface: &str) -> Result<String, Box<dyn std::error::Error>>{
    let mut get_networks_cmd = Command::new("iwctl");
    get_networks_cmd.args(["station", &interface, "get-networks"]);
    
    let result = get_networks_cmd.output()?;
    let text = String::from_utf8_lossy(&result.stdout);
    let networks = text
        .lines()
        .skip(4);

    let mut networks_list = Vec::new();
    for line in networks {

        let line_trimmed = line.trim();
        let line_noprefix = line_trimmed.strip_prefix("> ").unwrap_or(line_trimmed);
        let line_clean = line_noprefix.trim();

        if line_clean.is_empty() {
            continue;
        }

        let words: Vec<&str> = line_clean.split_whitespace().collect();

        if words.len() > 2 {
            let name_range = &words[0..words.len() - 2];
            let network_name = name_range.join(" ");
            networks_list.push(network_name);
        }
    }


    Ok(networks_list.join("\r\n"))
}

