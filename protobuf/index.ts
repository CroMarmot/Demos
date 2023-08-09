import axios from 'axios';
import { Add1Req, Add1Resp } from "./out/protodemo"

async function main(){
  const msg = Add1Req.encode({val:20}).finish();
  const response = await axios.post('http://127.0.0.1:6666/add_1_api', msg);
  const res = Add1Resp.decode(Buffer.from(await response.data, 'utf-8'))
  console.log(res.result == 21 ? "SUCCESS" : "FAILED");
}

main()
