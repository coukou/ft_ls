const os = require('os');
const { spawn } = require('child_process')

async function exec_ls(cmd, args, cb) {
	return new Promise((resolve, reject) => {
		const ls = spawn(cmd, args);
		const isLong = args.findIndex((v) => /-l/g.test(v)) !== -1;
		let str = '';
		ls.stdout.on('data', (d) => {
			str += d.toString().replace(/[ |\t]+/g, ' ');
		})
		ls.on('close', () => {
			resolve(str);
		})
	})
}

module.exports.ls_test = async function ls_test(args) {
	let aResult = await exec_ls('ls', ['-1'].concat(args));
	let bResult = await exec_ls('./ft_ls', args);

	if (os.platform() == 'linux')
		bResult = bResult.replace(/total ([0-9]+)/g, (m, v) => `total ${v / 2}`);

	let aLines = aResult.split('\n');
	let bLines = bResult.split('\n');

	if (os.platform() == 'linux' && /\:/g.test(aLines[0]))
		aLines = aLines.slice(1);

	return [aLines, bLines];
}
