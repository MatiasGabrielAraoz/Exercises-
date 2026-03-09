struct Color(i32, i32, i32);
struct Point(i32, i32, i32);

fn main() {

    let black: Color = Color(0,0,0);
    let origin: Point = Point(0, 0, 0);



    // let user1: User = build_user(String::from("pablitopro@gimeil.cum"),String::from("username"));
    let user1: User = User{
        active: true,
        username: String::from("pablito123"),
        email: String::from("pablitopro@gimeil.cum"),
        sign_in_count: 1,
    };
    let user2: User = User {
        username: String::from("jorgito321"),
        email: String::from("jorgitonub@gimeil.cum"),
        ..user1
    };
}

struct User {
    active: bool,
    username: String,
    email: String,
    sign_in_count: u64,
}

fn build_user(email: String, username: String) -> User {
    User {
        active: true,
        username,
        email,
        sign_in_count: 1,
    }
}
