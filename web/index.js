const sleep = (ms) => new Promise((resolve) => setTimeout(resolve, ms));

const headeruno = document.createElement("h1");
const h2 = document.createElement("h8");

main();

async function main(){
	const text = "hola"
	// "hola"
	// "aolh"
	//  ^
	//  kfdghffgfkjgdlfd
	headeruno.textContent = text;
	while (true){
		await sleep(1000);
		headeruno.textContent[-1] = headeruno.textContent[0];
		await sleep(1000);
		headeruno.textContent[0] = headeruno.textContent[-1];
		await sleep(1000);
		document.body.appendChild(headeruno);
	}
}
