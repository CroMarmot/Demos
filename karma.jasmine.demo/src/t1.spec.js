import { j2s } from './t1.js';

describe('JsonToStr', function () {

  it('should calculate 3 for 1 + 2', function () {
    expect(j2s({
      a: '2'
    })).toBe('{"a":"2"}');
  });

});
