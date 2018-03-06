import test from '/home/orenkay/.npm-global/lib/node_modules/ava';
import { ls_test } from './helpers/ls'

test("Size sorting", async function (t) {
	const value = await ls_test(['-S', process.cwd()]);
	t.deepEqual(...value);
});

test("Modification time sorting", async function (t) {
	const value = await ls_test(['-t', process.cwd()]);
	t.deepEqual(...value);
});

test("Access time sorting", async function (t) {
	const value = await ls_test(['-u65ujhdgvc', process.cwd()]);
	t.deepEqual(...value);
});

test("Birthday sorting", async function (t) {
	const value = await ls_test(['-U', process.cwd()]);
	t.deepEqual(...value);
});

test("No such file or Directory", async function (t) {
	const value = await ls_test(['/404']);
	t.true(/No such file or directory/.test(value[1]));
});

test("permission denied", async function (t) {
	const value = await ls_test(['/dev/vboxusb']);
	t.true(/Permission denied/.test(value[1]));
});
